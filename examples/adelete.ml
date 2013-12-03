open Zookeeper

let acl = [|{perms = 0x1f; scheme = "auth"; id = ""}|]

let watcher_fn zhandle event_type conn_state path watcher_ctx =
  if event_type = Zookeeper.ZOO_SESSION_EVENT then
    if conn_state = Zookeeper.ZOO_CONNECTED_STATE then
      print_string "Connected to zookeeper service successfully.\n"
    else if conn_state = Zookeeper.ZOO_EXPIRED_SESSION_STATE then
      print_string "Zookeeper session expired\n"

let void_completion rc data =
  if rc = Zookeeper.ZOK then
    print_string ("Delete node Ok with returned value: " ^ value ^ "\n")
  else
    print_string "Failed to delete node.\n"

let connect host = init host watcher_fn 3600 {client_id = 0L; passwd=""} "hello world" 0

let adelete_node handle path = adelete handle path -1 void_completion "(*adelete*)"

let handle = connect "127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183";;

read_line();;

let _ = adelete_node handle "/example";;

read_line();;
