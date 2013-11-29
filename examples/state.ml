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

let status state_type =
  if state_type = Zookeeper.ZOO_EXPIRED_SESSION_STATE then
    print_string "Zookeeper.ZOO_EXPIRED_SESSION_STATE.\n"
  else if state_type = ZOO_AUTH_FAILED_STATE then
    print_string "Zookeeper.ZOO_AUTH_FAILED_STATE.\n"
  else if  state_type = ZOO_CONNECTING_STATE then
    print_string "Zookeeper.ZOO_CONNECTING_STATE.\n"
  else if  state_type = ZOO_ASSOCIATING_STATE then
    print_string "Zookeeper.ZOO_ASSOCIATING_STATE.\n"
  else if state_type = ZOO_CONNECTED_STATE then
    print_string "Zookeeper.ZOO_CONNECTED_STATE.\n"
  else 
    print_string "Zookeeper.XXXXXXXXXXXXXXXXXXX.\n"

let connect host = init host watcher_fn 3600 {client_id = 0L; passwd=""} "hello world" 0

let handle = connect "127.0.0.2:2183"

let state_type = zstate handle

let _ = status state_type;;

read_line();;
