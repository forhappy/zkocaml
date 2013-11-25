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

/**
 * Create a node.
 *
 * This method will create a node in ZooKeeper. A node can only be created if
 * it does not already exists. The Create Flags affect the creation of nodes.
 * If ZOO_EPHEMERAL flag is set, the node will automatically get removed if the
 * client session goes away. If the ZOO_SEQUENCE flag is set, a unique
 * monotonically increasing sequence number is appended to the path name. The
 * sequence number is always fixed length of 10 digits, 0 padded.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path The name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @value The data to be stored in the node.
 *
 * @acl The initial ACL of the node. The ACL must not be null or empty.
 *
 * @flags this parameter can be set to 0 for normal create or an OR
 * of the Create Flags
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the parent node does not exist.
 *   ZNODEEXISTS the node already exists
 *   ZNOAUTH the client does not have permission.
 *   ZNOCHILDRENFOREPHEMERALS cannot create children of ephemeral nodes.
 *
 * @data The data that will be passed to the completion routine when the
 * function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_acreate_native(value zh, value path, value val, value acl,
                value flags, value completion, value data)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_acreate_bytecode(value *argv, int argn)
{
  return zkocaml_acreate_native(argv[0], argv[1], argv[2], argv[3],
                             argv[4], argv[5], argv[6]);
}

/**
 * Delete a node in zookeeper.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @version the expected version of the node. The function will fail if the
 * actual version of the node does not match the expected version.
 * If -1 is used the version check will not take place.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADVERSION expected version does not match actual version.
 *   ZNOTEMPTY children are present; node cannot be deleted.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_adelete(value zh, value path, value version,
                value completion, value data)
{
  CAMLparam1(zh);
}

/**
 * Checks the existence of a node in zookeeper.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify the
 * client if the node changes. The watch will be set even if the node does not
 * exist. This allows clients to watch for nodes to appear.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when the
 * function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_aexists(value zh, value path, value watch,
                value completion, value data)
{
  CAMLparam1(zh);
}

/**
 * Checks the existence of a node in zookeeper.
 *
 * This function is similar to zoo_axists except it allows one specify
 * a watcher object - a function pointer and associated context. The function
 * will be called once the watch has fired. The associated context data will be
 * passed to the function as the watcher context parameter.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watcher if non-null a watch will set on the specified znode on the server.
 * The watch will be set even if the node does not exist. This allows clients
 * to watch for nodes to appear.
 *
 * @watcher_ctx user specific data, will be passed to the watcher callback.
 * Unlike the global context set by zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when the
 * function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_awexists_native(value zh, value path, value watcher,
                 value watcher_ctx, value completion, value data)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awexists_bytecode(value *argv, int argn)
{
  return zkocaml_awexists_native(argv[0], argv[1], argv[2],
                                 argv[3], argv[4], argv[5]);
}

/**
 * Gets the data associated with a node.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either in ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_aget(value zh, value path, value watch, value completion, value data)
{
  CAMLparam1(zh);
}

/**
 * Gets the data associated with a node.
 *
 * This function is similar to zoo_aget except it allows one specify
 * a watcher object rather than a boolean watch flag.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watcher if non-null, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @watcher_ctx user specific data, will be passed to the watcher callback.
 * Unlike the global context set by zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either in ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_awget_native(value zh, value path, value watcher,
                     value watcher_ctx, value completion, value data)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awget_bytecode(value *argv, int argn)
{
  return zkocaml_awget_native(argv[0], argv[1], argv[2],
                              argv[3], argv[4], argv[5]);
}

/**
 * Sets the data associated with a node.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @buffer the buffer holding data to be written to the node.
 *
 * @version the expected version of the node. The function will fail if
 * the actual version of the node does not match the expected version. If -1 is
 * used the version check will not take place. * completion: If null,
 * the function will execute synchronously. Otherwise, the function will return
 * immediately and invoke the completion routine when the request completes.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADVERSION expected version does not match actual version.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_aset_native(value zh, value path, value buffer,
             value version, value completion, value data)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_aset_bytecode(value *argv, int argn)
{
  return zkocaml_aset_native(argv[0], argv[1], argv[2],
                              argv[3], argv[4], argv[5]);
}

/**
 * Lists the children of a node.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_aget_children(value zh, value path, value watch,
                      value completion, value data)
{
  CAMLparam1(zh);
}

/**
 * Lists the children of a node.
 *
 * This function is similar to zoo_aget_children except it allows one specify
 * a watcher object rather than a boolean watch flag.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watcher if non-null, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @watcher_ctx user specific data, will be passed to the watcher callback.
 * Unlike the global context set by zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *
 * @data the data that will be passed to the completion routine when
 * the function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_awget_children_native(value zh, value path, value watcher,
                       value watcher_ctx, value completion, value data)
{
  CAMLparam1(zh);
}

CAMLprim value
zkocaml_awget_children_bytecode(value *argv, int argn)
{
  return zkocaml_awget_children_native(argv[0], argv[1], argv[2],
                                       argv[3], argv[4], argv[5]);
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

