#include "PedidoDAO.h"

#include "sqlite3.h"

BD &PedidoDAO::db = BD::get_instance();

PedidoDAO::PedidoDAO() = default;

void PedidoDAO::insert(Pedido &pedido) {
  sqlite3_stmt *stmt;
  std::string sql = "INSERT INTO Pedido (id_usuario, direccion, fecha, estado) "
                    "VALUES (?, ?, ?, ?);";
  int result = db.execute_query(sql, &stmt);
  if (result != 0) {
    std::cout << "Error preparando la consulta" << std::endl;
    return;
  }
  sqlite3_bind_int(stmt, 1, pedido.getIdUsuario());
  sqlite3_bind_text(stmt, 2, pedido.getDireccion().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int64(stmt, 3, pedido.getFecha());
  sqlite3_bind_int(stmt, 4, pedido.getEstado());
  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    std::cout << "Error ejecutando la inserción" << std::endl;
  } else {
    std::cout << "Pedido insertado correctamente." << std::endl;
  }
  sqlite3_finalize(stmt);

  long long pedido_id = sqlite3_last_insert_rowid(db.get_db());
  if (!pedido.getMapa().empty()) {
    std::string sql_detalle = "INSERT INTO PedidoDetalle (id_pedido, id_plato, "
                              "cantidad, precio_unitario) VALUES (?, ?, ?, ?);";
    std::string sql_precio_plato = "SELECT precio FROM Plato WHERE id = ?;";

    for (const auto &item : pedido.getMapa()) {
      int id_plato = item.first;
      int cantidad = item.second;
      double precio_unitario = 0.0;

      // Fetch precio_unitario from Plato table
      sqlite3_stmt *stmt_precio;
      if (db.execute_query(sql_precio_plato, &stmt_precio) == SQLITE_OK) {
        sqlite3_bind_int(stmt_precio, 1, id_plato);
        if (sqlite3_step(stmt_precio) == SQLITE_ROW) {
          precio_unitario = sqlite3_column_double(stmt_precio, 0);
        } else {
          std::cerr << "Error: Plato con ID " << id_plato
                    << " no encontrado para obtener precio." << std::endl;
          // Decide error handling: skip this item, fail transaction, etc.
          // For now, we'll insert with 0.0 or skip. Let's skip if price not
          // found.
          sqlite3_finalize(stmt_precio);
          continue;
        }
        sqlite3_finalize(stmt_precio);
      } else {
        std::cerr << "Error preparing query to fetch plato price: "
                  << sqlite3_errmsg(db.get_db()) << std::endl;
        continue;
      }

      sqlite3_stmt *stmt_det;
      if (db.execute_query(sql_detalle, &stmt_det) == SQLITE_OK) {
        sqlite3_bind_int64(stmt_det, 1, pedido_id);
        sqlite3_bind_int(stmt_det, 2, id_plato);
        sqlite3_bind_int(stmt_det, 3, cantidad);
        sqlite3_bind_double(stmt_det, 4, precio_unitario);

        if (sqlite3_step(stmt_det) != SQLITE_DONE) {
          std::cerr << "Error ejecutando la inserción en PedidoDetalle: "
                    << sqlite3_errmsg(db.get_db()) << std::endl;
        }
        sqlite3_finalize(stmt_det);
      } else {
        std::cerr << "Error preparing PedidoDetalle insert query: "
                  << sqlite3_errmsg(db.get_db()) << std::endl;
      }
    }
    std::cout << "Detalles del pedido insertados." << std::endl;
  }
}

void PedidoDAO::del(Pedido &pedido) {
  sqlite3_stmt *stmt;
  std::string sql = "DELETE FROM Pedido WHERE id_pedido = ?;";
  int result = db.execute_query(sql, &stmt);
  if (result != 0) {
    std::cout << "Error preparando la consulta" << std::endl;
    return;
  }
  sqlite3_bind_int(stmt, 1, pedido.getIdPedido());
  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE) {
    std::cout << "Error ejecutando la eliminación" << std::endl;
  } else {
    std::cout << "Pedido eliminado correctamente." << std::endl;
  }
  sqlite3_finalize(stmt);
}

Pedido *PedidoDAO::select(Pedido &pedido_input) {
  sqlite3_stmt *stmt;
  std::string sql = "SELECT id_pedido, id_usuario, direccion, fecha, estado "
                    "FROM Pedido WHERE id_pedido = ?;";
  db.abrir_conexion();
  if (db.execute_query(sql, &stmt) != SQLITE_OK) {
    std::cerr << "Error preparando la consulta de selección de Pedido: "
              << sqlite3_errmsg(db.get_db()) << std::endl;
    return nullptr;
  }

  sqlite3_bind_int(stmt, 1, pedido_input.getIdPedido());

  Pedido *p = nullptr;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    int id_pedido = sqlite3_column_int(stmt, 0);
    int id_usuario = sqlite3_column_int(stmt, 1);
    std::string direccion =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    // Assuming fecha is stored as a string representation of time_t (Unix
    // timestamp)
    time_t fecha = static_cast<time_t>(sqlite3_column_int64(stmt, 3));
    int estado = sqlite3_column_int(stmt, 4);

    p = new Pedido(id_pedido, id_usuario, direccion, fecha, estado);

    // Fetch PedidoDetalle
    sqlite3_stmt *stmt_det;
    std::string sql_det =
        "SELECT id_plato, cantidad FROM PedidoDetalle WHERE id_pedido = ?;";
    if (db.execute_query(sql_det, &stmt_det) == SQLITE_OK) {
      sqlite3_bind_int(stmt_det, 1, id_pedido);
      while (sqlite3_step(stmt_det) == SQLITE_ROW) {
        int id_plato = sqlite3_column_int(stmt_det, 0);
        int cantidad = sqlite3_column_int(stmt_det, 1);
        p->agregarPlato(id_plato, cantidad);
      }
      sqlite3_finalize(stmt_det);
    } else {
      std::cerr << "Error preparando la consulta de PedidoDetalle: "
                << sqlite3_errmsg(db.get_db()) << std::endl;
      // p is still valid but its map might be empty
    }
  } else {
    std::cout << "No existe este pedido con ID: " << pedido_input.getIdPedido()
              << std::endl;
  }

  sqlite3_finalize(stmt);
  return p;
}

std::vector<Pedido> PedidoDAO::historial(Usuario &usuario) {
    sqlite3_stmt *stmt;
    // It's generally better to use explicit JOIN syntax
    std::string sql =
            "SELECT p.id_pedido, p.id_usuario, p.direccion, p.fecha, p.estado "
            "FROM Pedido p JOIN Usuario u ON p.id_usuario = u.id WHERE u.dni = ?;";

    // It's good practice to ensure the DB connection is open.
    // db.abrir_conexion(); // If your BD class requires explicit opening per operation.

    int result = db.execute_query(sql, &stmt);
    if (result != SQLITE_OK) { // Assuming execute_query returns SQLITE_OK (0) on success
        std::cerr << "Error preparing the Pedido historial query: " << sqlite3_errmsg(db.get_db()) << std::endl;
        return {};
    }

    sqlite3_bind_text(stmt, 1, usuario.getDni().c_str(), -1, SQLITE_STATIC);

    std::vector<Pedido> pedidos_list; // Renamed to avoid confusion if 'pedidos' is a member
    int result_step;
    while ((result_step = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id_pedido = sqlite3_column_int(stmt, 0);
        int id_usuario_db = sqlite3_column_int(stmt, 1); // Renamed to avoid conflict with function param
        std::string direccion = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        // Assuming fecha is stored as a string representation of time_t (Unix timestamp)
        // Or if it's a numeric Unix timestamp, use sqlite3_column_int64
        time_t fecha;
        const char* fecha_text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        if (fecha_text) {
            try {
                fecha = std::stoll(fecha_text); // Use stoll for time_t if it's a string of a number
            } catch (const std::exception& e) {
                std::cerr << "Error converting fecha string to time_t: " << fecha_text << " - " << e.what() << std::endl;
                fecha = 0; // Default or error value
            }
        } else {
            fecha = 0; // Default or error value
        }

        int estado = sqlite3_column_int(stmt, 4);

        // Create Pedido object. Ensure your Pedido constructor can be called like this,
        // or that you have a constructor that takes these params and initializes an empty map,
        // which you then fill.
        Pedido current_pedido(id_pedido, id_usuario_db, direccion, fecha, estado);

        // Fetch PedidoDetalle for current_pedido
        sqlite3_stmt *stmt_det;
        std::string sql_det = "SELECT id_plato, cantidad FROM PedidoDetalle WHERE id_pedido = ?;";
        if (db.execute_query(sql_det, &stmt_det) == SQLITE_OK) {
            sqlite3_bind_int(stmt_det, 1, id_pedido);
            while (sqlite3_step(stmt_det) == SQLITE_ROW) {
                int id_plato = sqlite3_column_int(stmt_det, 0);
                int cantidad = sqlite3_column_int(stmt_det, 1);
                current_pedido.agregarPlato(id_plato, cantidad); // Assumes Pedido class has agregarPlato
            }
            sqlite3_finalize(stmt_det);
        } else {
            std::cerr << "Error preparing PedidoDetalle query for pedido ID " << id_pedido << ": " << sqlite3_errmsg(db.get_db()) << std::endl;
        }
        pedidos_list.push_back(current_pedido);
    }

    if (result_step != SQLITE_DONE) {
        std::cerr << "Error iterating over Pedido historial results: " << sqlite3_errmsg(db.get_db()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return pedidos_list;
}