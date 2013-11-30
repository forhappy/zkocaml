type zhandle
type client_id = { client_id : int64; passwd : string; }
type acl = { perms : int; scheme : string; id : string; }
type acls = acl array
type strings = string array
type stat = {
  czxid : int64;
  mzxid : int64;
  ctime : int64;
  mtime : int64;
  version : int;
  cversion : int;
  aversion : int;
  ephemeral_owner : int64;
  data_length : int;
  num_children : int;
  pzxid : int;
}
type error =
    ZOK
  | ZSYSTEMERROR
  | ZRUNTIMEINCONSISTENCY
  | ZDATAINCONSISTENCY
  | ZCONNECTIONLOSS
  | ZMARSHALLINGERROR
  | ZUNIMPLEMENTED
  | ZOPERATIONTIMEOUT
  | ZBADARGUMENTS
  | ZINVALIDSTATE
  | ZAPIERROR
  | ZNONODE
  | ZNOAUTH
  | ZBADVERSION
  | ZNOCHILDRENFOREPHEMERALS
  | ZNODEEXISTS
  | ZNOTEMPTY
  | ZSESSIONEXPIRED
  | ZINVALIDCALLBACK
  | ZINVALIDACL
  | ZAUTHFAILED
  | ZCLOSING
  | ZNOTHING
  | ZSESSIONMOVED
type event =
    ZOO_CREATED_EVENT
  | ZOO_DELETED_EVENT
  | ZOO_CHANGED_EVENT
  | ZOO_CHILD_EVENT
  | ZOO_SESSION_EVENT
  | ZOO_NOTWATCHING_EVENT
type perm =
    ZOO_PERM_READ
  | ZOO_PERM_WRITE
  | ZOO_PERM_CREATE
  | ZOO_PERM_DELETE
  | ZOO_PERM_ADMIN
  | ZOO_PERM_ALL
type state =
    ZOO_EXPIRED_SESSION_STATE
  | ZOO_AUTH_FAILED_STATE
  | ZOO_CONNECTING_STATE
  | ZOO_ASSOCIATING_STATE
  | ZOO_CONNECTED_STATE
type create_flag = ZOO_EPHEMERAL | ZOO_SEQUENCE
type log_level =
    ZOO_LOG_LEVEL_ERROR
  | ZOO_LOG_LEVEL_WARN
  | ZOO_LOG_LEVEL_INFO
  | ZOO_LOG_LEVEL_DEBUG
type watcher_callback = zhandle -> event -> state -> string -> string -> unit
type void_completion_callback = error -> string -> unit
type stat_completion_callback = error -> stat -> string -> unit
type data_completion_callback =
    error -> string -> int -> stat -> string -> unit
type strings_completion_callback = error -> strings -> string -> unit
type strings_stat_completion_callback =
    error -> strings -> stat -> string -> unit
type string_completion_callback = error -> string -> string -> unit
type acl_completion_callback = error -> acls -> stat -> string -> unit
external init :
  string -> watcher_callback -> int -> client_id -> string -> int -> zhandle
  = "zkocaml_init_bytecode" "zkocaml_init_native"
external close : zhandle -> error = "zkocaml_close"
external client_id : zhandle -> client_id = "zkocaml_client_id"
external recv_timeout : zhandle -> int = "zkocaml_recv_timeout"
external get_context : zhandle -> string = "zkocaml_get_context"
external set_context : zhandle -> string -> unit = "zkocaml_set_context"
external set_watcher : zhandle -> watcher_callback -> watcher_callback
  = "zkocaml_set_watcher"
external get_connected_host : zhandle -> string
  = "zkocaml_get_connected_host"
external zstate : zhandle -> state = "zkocaml_state"
external acreate :
  zhandle ->
  string ->
  string ->
  acls -> create_flag -> string_completion_callback -> string -> error
  = "zkocaml_acreate_bytecode" "zkocaml_acreate_native"
external adelete :
  zhandle -> string -> int -> void_completion_callback -> string -> error
  = "zkocaml_adelete"
external aexists :
  zhandle -> string -> int -> stat_completion_callback -> string -> error
  = "zkocaml_aexists"
external awexists :
  zhandle ->
  string ->
  watcher_callback -> string -> stat_completion_callback -> string -> error
  = "zkocaml_awexists_native" "zkocaml_awexists_bytecode"
external aget :
  zhandle -> string -> int -> data_completion_callback -> string -> error
  = "zkocaml_aget"
external awget :
  zhandle ->
  string ->
  watcher_callback -> string -> data_completion_callback -> string -> error
  = "zkocaml_awget_native" "zkocaml_awget_bytecode"
external aset :
  zhandle ->
  string -> string -> int -> stat_completion_callback -> string -> error
  = "zkocaml_aset_native" "zkocaml_aset_bytecode"
external aget_children :
  zhandle -> string -> int -> strings_completion_callback -> string -> error
  = "zkocaml_aget_children"
external awget_children :
  zhandle ->
  string ->
  watcher_callback ->
  string -> strings_completion_callback -> string -> error
  = "zkocaml_awget_children_native" "zkocaml_awget_children_bytecode"
external aget_children2 :
  zhandle ->
  string -> int -> strings_stat_completion_callback -> string -> error
  = "zkocaml_aget_children2"
external awget_children2 :
  zhandle ->
  string ->
  watcher_callback ->
  string -> strings_stat_completion_callback -> string -> error
  = "zkocaml_awget_children2_native" "zkocaml_awget_children2_bytecode"
external async :
  zhandle -> string -> string_completion_callback -> string -> error
  = "zkocaml_async"
external aget_acl :
  zhandle ->
  string -> int -> acls -> acl_completion_callback -> string -> error
  = "zkocaml_aget_acl"
external aset_acl :
  zhandle -> string -> acl_completion_callback -> string -> error
  = "zkocaml_aset_acl_native" "zkocaml_aset_acl_bytecode"
external zerror : int -> string = "zkocaml_zerror"
external add_auth :
  zhandle -> string -> string -> void_completion_callback -> string -> error
  = "zkocaml_add_auth"
