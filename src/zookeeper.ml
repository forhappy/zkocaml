(* ZkOCaml: OCaml Binding For Apache ZooKeeper
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *)

type error =
  ZOK (*!< Everything is OK *)

  (** System and server-side errors. *)
  (* This is never thrown by the server, it shouldn't be used other than *)
  (* to indicate a range. Specifically error codes greater than this *)
  (* value, but lesser than {ZAPIERROR}, are system errors.*)
  | ZSYSTEMERROR
  | ZRUNTIMEINCONSISTENCY (*!< A runtime inconsistency was found *)
  | ZDATAINCONSISTENCY    (*!< A data inconsistency was found *)
  | ZCONNECTIONLOSS       (*!< Connection to the server has been lost *)
  | ZMARSHALLINGERROR     (*!< Error while marshalling or unmarshalling data *)
  | ZUNIMPLEMENTED        (*!< Operation is unimplemented *)
  | ZOPERATIONTIMEOUT     (*!< Operation timeout *)
  | ZBADARGUMENTS         (*!< Invalid arguments *)
  | ZINVALIDSTATE         (*!< Invliad zhandle state *)

  (** API errors. *)
  (* This is never thrown by the server, it shouldn't be used other than *)
  (* to indicate a range. Specifically error codes greater than this *)
  (* value are API errors (while values less than this indicate a *)
  (* ZSYSTEMERROR. *)
  | ZAPIERROR
  | ZNONODE                (*!< Node does not exist *)
  | ZNOAUTH                (*!< Not authenticated *)
  | ZBADVERSION            (*!< Version conflict *)
  | ZNOCHILDRENFOREPHEMERALS (*!< Ephemeral nodes may not have children *)
  | ZNODEEXISTS            (*!< The node already exists *)
  | ZNOTEMPTY              (*!< The node has children *)
  | ZSESSIONEXPIRED        (*!< The session has been expired by the server *)
  | ZINVALIDCALLBACK       (*!< Invalid callback specified *)
  | ZINVALIDACL            (*!< Invalid ACL specified *)
  | ZAUTHFAILED            (*!< Client authentication failed *)
  | ZCLOSING               (*!< ZooKeeper is closing *)
  | ZNOTHING               (*!< (not error) no server responses to process *)
  | ZSESSIONMOVED          (*!<session moved to another server, so operation is ignored *)

