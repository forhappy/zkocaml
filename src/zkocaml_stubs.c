/* ZkOCaml: OCaml Binding For Apache ZooKeeper.
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
 */

#include <stdlib.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/signals.h>

#include <zookeeper/zookeeper.h>

#define zhandle_struct_val(v) (*(zhandle_t **)Data_custom_val(v))

static void
zhandle_struct_finalize(value ve)
{
}

static int
zhandle_struct_compare(value v1, value v2)
{
  return 1;
}

static long
zhandle_struct_hash(value v)
{
  return (long) zhandle_struct_val(v);
}

static struct custom_operations zhandle_struct_ops = {
  "org.apache.zookeeper",
  zhandle_struct_finalize,
  zhandle_struct_compare,
  zhandle_struct_hash,
  custom_serialize_default,
  custom_deserialize_default
};

/**
 * Create a handle to used communicate with zookeeper.
 *
 * This method creates a new handle and a zookeeper session that corresponds
 * to that handle. Session establishment is asynchronous, meaning that the
 * session should not be considered established until (and unless) an
 * event of state ZOO_CONNECTED_STATE is received.
 *
 * @host Comma separated host:port pairs, each corresponding to a zk
 *   server. e.g. "127.0.0.1:3000,127.0.0.1:3001,127.0.0.1:3002"
 *
 * @watcher_fn The global watcher callback function. When notifications are
 *   triggered this function will be invoked.
 *
 * @clientid The id of a previously established session that this
 *   client will be reconnecting to. Pass 0 if not reconnecting to a previous
 *   session. Clients can access the session id of an established, valid,
 *   connection by calling zoo_client_id. If the session corresponding to
 *   the specified clientid has expired, or if the clientid is invalid for 
 *   any reason, the returned zhandle_t will be invalid -- the zhandle_t
 *   state will indicate the reason for failure (typically
 *   ZOO_EXPIRED_SESSION_STATE).
 *
 * @context The handback object that will be associated with this instance 
 *   of zhandle_t. Application can access it (for example, in the watcher
 *   callback) using zoo_get_context. The object is not used by zookeeper
 *   internally and can be null.
 *
 * @flags Reserved for future use. Should be set to zero.
 *
 * @return A pointer to the opaque zhandle structure. If it fails to create
 * a new zhandle the function returns NULL and the errno variable indicates
 * the reason.
 */

CAMLprim value
zkocaml_init_native(value host, value watcher_fn, value recv_timeout,
                    value clientid, value context, value flag)
{
  CAMLparam1(host);
}

CAMLprim value
zkocaml_init_bytecode(value *argv, int argn)
{
  return zkocaml_init_native(argv[0], argv[1], argv[2],
                             argv[3], argv[4], argv[5]);
}

CAMLprim value
zkocaml_close(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_client_id(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_recv_timeout(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_get_context(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set_context(value zh, value context)
{
  CAMLparam1(zh);
}


CAMLprim value
zkocaml_set_watcher(value zh, value watcher_fn)
{
  CAMLparam1(zh);
}


CAMLprim value
zkocaml_get_connected_host(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_state(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_acreate(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_adelete(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aexists(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awexists(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aget(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awget(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aset(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aget_children(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awget_children(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aget_children2(value zh)
{
  CAMLparam1(zh);
}


CAMLprim value
zkocaml_awget_children2(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_async(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aget_acl(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aset_acl(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_zerror(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_add_auth(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_is_unrecoverable(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set_debug_level(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set_log_stream(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_deterministic_conn_order(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_create(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_delete(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_exists(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_wexists(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_get(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_wget(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set2(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_get_children(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_wget_children(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_get_children2(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_wget_children2(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_get_acl(value zh)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_set_acl(value zh)
{
  CAMLparam1(zh);
}

