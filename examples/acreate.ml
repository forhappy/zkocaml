open Zookeeper

let acl = [|{perms = 0x1f; scheme = "auth"; id = ""}|]
let create_flag = Zookeeper.ZOO_SEQUENCE

let watcher_fn zhandle event_type conn_state path watcher_ctx =
  if event_type = Zookeeper.ZOO_SESSION_EVENT then
    if conn_state = Zookeeper.ZOO_CONNECTED_STATE then
      print_string "Connected to zookeeper service successfully.\n"
    else if conn_state = Zookeeper.ZOO_EXPIRED_SESSION_STATE then
      print_string "Zookeeper session expired\n"

let string_completion rc value data =
  if rc = Zookeeper.ZOK then
    print_string ("Create node Ok with returned value: " ^ value ^ "\n")
  else
    print_string "Failed to create node.\n"

let connect host = init host watcher_fn 3600 {client_id = 0L; passwd=""} "hello world" 0

let acreate_node handle path value = acreate handle path value acl Zookeeper.ZOO_SEQUENCE string_completion "(*acreate*)"

let handle = connect "127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183" 

(* let _ = let handle = connect "127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183"
 * in acreate_node handle "/example" "hello";; *)

let _ = acreate_node handle "/example" "hello";;

read_line();;
