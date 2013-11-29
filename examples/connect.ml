open Zookeeper

let watcher_fn zhandle event_type conn_state path watcher_ctx =
  if event_type = Zookeeper.ZOO_SESSION_EVENT then
    if conn_state = Zookeeper.ZOO_CONNECTED_STATE then
      print_string "Connected to zookeeper service successfully.\n"
    else if conn_state = Zookeeper.ZOO_EXPIRED_SESSION_STATE then
      print_string "Zookeeper session expired\n"

let zh = init "127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183" watcher_fn 3600 {client_id = 0L; passwd=""} "hello world" 0;;

read_line();;
