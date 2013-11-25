/* ZkOCaml: OCaml Binding For Apache ZooKeeper
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

#ifndef _ZKOCAML_H_
#define _ZKOCAML_H_

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
                    value clientid, value context, value flag);

CAMLprim value
zkocaml_init_bytecode(value *argv, int argn);

/**
 * Close the zookeeper handle and free up any resources.
 *
 * After this call, the client session will no longer be valid. The function
 * will flush any outstanding send requests before return. As a result it may
 * block.
 *
 * This method should only be called only once on a zookeeper handle. Calling
 * twice will cause undefined (and probably undesirable behavior). Calling any other
 * zookeeper method after calling close is undefined behaviour and should be avoided.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @return a result code. Regardless of the error code returned, the zhandle
 * will be destroyed and all resources freed.
 *   ZOK - success
 *   ZBADARGUMENTS - invalid input parameters
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 *   ZOPERATIONTIMEOUT - failed to flush the buffers within the specified timeout.
 *   ZCONNECTIONLOSS - a network error occured while attempting to send request to server
 *   ZSYSTEMERROR -- a system (OS) error occured; it's worth checking errno to get details
 */
CAMLprim value
zkocaml_close(value zh);

/**
 * Return the client session id, only valid if the connections
 * is currently connected (ie. last watcher state is ZOO_CONNECTED_STATE)
 */
CAMLprim value
zkocaml_client_id(value zh);

/**
 * Return the timeout for this session, only valid if the connections
 * is currently connected (ie. last watcher state is ZOO_CONNECTED_STATE). This
 * value may change after a server re-connect.
 */
CAMLprim value
zkocaml_recv_timeout(value zh);

/**
 * Return the context for this handle.
 */
CAMLprim value
zkocaml_get_context(value zh);

/**
 * Set the context for this handle.
 */
CAMLprim value
zkocaml_set_context(value zh, value context);

/**
 * Set a watcher function
 * @return previous watcher function
 */
CAMLprim value
zkocaml_set_watcher(value zh, value watcher_fn);

/**
 * Returns the socket address for the current connection
 *
 * @return socket address of the connected host or NULL on failure, only valid if the
 * connection is current connected
 */
CAMLprim value
zkocaml_get_connected_host(value zh);

/**
 * Get the state of the zookeeper connection.
 *
 * The return value will be one of the state consts.
 */
CAMLprim value
zkocaml_state(value zh);

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
                       value flags, value completion, value data);

CAMLprim value
zkocaml_acreate_bytecode(value *argv, int argn);

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
                value completion, value data);

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
                        value watcher_ctx, value completion, value data);

CAMLprim value
zkocaml_awexists_bytecode(value *argv, int argn);

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
zkocaml_aget(value zh, value path, value watch, value completion, value data);

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
                     value watcher_ctx, value completion, value data);

CAMLprim value
zkocaml_awget_bytecode(value *argv, int argn);

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
             value version, value completion, value data);

CAMLprim value
zkocaml_aset_bytecode(value *argv, int argn);

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
                      value completion, value data);

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
                       value watcher_ctx, value completion, value data);

CAMLprim value
zkocaml_awget_children_bytecode(value *argv, int argn);

/**
 * Lists the children of a node, and get the parent stat.
 *
 * This function is new in version 3.3.0
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
zkocaml_aget_children2(value zh, value path, value watch,
                       value completion, value data);

/**
 * Lists the children of a node, and get the parent stat.
 *
 * This function is similar to zoo_aget_children2 except it allows one specify
 * a watcher object rather than a boolean watch flag.
 *
 * This function is new in version 3.3.0
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
zkocaml_awget_children2_native(value zh, value path, value watcher,
                               value watcher_ctx, value completion, value data);

CAMLprim value
zkocaml_awget_children2_bytecode(value *argv, int argn);

/**
 * Flush leader channel.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
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
zkocaml_async(value zh, value path, value completion, value data);

/**
 * Gets the acl associated with a node.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
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
zkocaml_aget_acl(value zh, value path, value completion, value data);

/**
 * Sets the acl associated with a node.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @buffer the buffer holding the acls to be written to the node.
 *
 * @completion the routine to invoke when the request completes. The completion
 * will be triggered with one of the following codes passed in as the rc argument:
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZINVALIDACL invalid ACL specified
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
zkocaml_aset_acl(value zh, value path, value buffer,
                 value completion, value data);

/**
 * Return an error string.
 *
 * @rc return code.
 * @return string corresponding to the return code
 */
CAMLprim value
zkocaml_zerror(value rc);

/**
 * Specify application credentials.
 *
 * The application calls this function to specify its credentials for purposes
 * of authentication. The server will use the security provider specified by
 * the scheme parameter to authenticate the client connection. If the
 * authentication request has failed:
 * - the server connection is dropped
 * - the watcher is called with the ZOO_AUTH_FAILED_STATE value as the state
 * parameter.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @scheme the id of authentication scheme. Natively supported:
 * "digest" password-based authentication
 *
 * @cert application credentials. The actual value depends on the scheme.
 *
 * @completion the routine to invoke when the request completes. One of
 * the following result codes may be passed into the completion callback:
 *   ZOK operation completed successfully
 *   ZAUTHFAILED authentication failed
 *
 * @data the data that will be passed to the completion routine when the
 * function completes.
 *
 * @return ZOK on success or one of the following errcodes on failure:
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 *   ZSYSTEMERROR - a system error occured
 */
CAMLprim value
zkocaml_add_auth(value zh, value scheme, value cert, value completion, value data);

/**
 * Checks if the current zookeeper connection state can't be recovered.
 *
 *  The application must close the zhandle and try to reconnect.
 *
 * @zh the zookeeper handle (see zookeeper_init)
 * @return ZINVALIDSTATE if connection is unrecoverable
 */
CAMLprim value
zkocaml_is_unrecoverable(value zh);

/**
 * Sets the debugging level for the library
 */
CAMLprim value
zkocaml_set_debug_level(value log_level);

/**
 * Sets the stream to be used by the library for logging
 *
 * The zookeeper library uses stderr as its default log stream. Application
 * must make sure the stream is writable. Passing in NULL resets the stream
 * to its default value (stderr).
 */
CAMLprim value
zkocaml_set_log_stream(value log_stream);

/**
 * Enable/disable quorum endpoint order randomization
 *
 * Note: typically this method should NOT be used outside of testing.
 *
 * If passed a non-zero value, will make the client connect to quorum peers
 * in the order as specified in the zookeeper_init() call.
 * A zero value causes zookeeper_init() to permute the peer endpoints
 * which is good for more even client connection distribution among the
 * quorum peers.
 */
CAMLprim value
zkocaml_deterministic_conn_order(value yes_or_no);

/**
 * Create a node synchronously.
 *
 * This method will create a node in ZooKeeper. A node can only be created if
 * it does not already exists. The Create Flags affect the creation of nodes.
 * If ZOO_EPHEMERAL flag is set, the node will automatically get removed if the
 * client session goes away. If the ZOO_SEQUENCE flag is set, a unique
 * monotonically increasing sequence number is appended to the path name.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init.
 *
 * @path The name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @val The data to be stored in the node.
 *
 * @acl The initial ACL of the node. The ACL must not be null or empty.
 *
 * @flags this parameter can be set to 0 for normal create or an OR
 * of the Create Flags
 *
 * @path_buffer Buffer which will be filled with the path of the
 * new node (this might be different than the supplied path
 * because of the ZOO_SEQUENCE flag).  The path string will always be
 * null-terminated. This parameter may be NULL if path_buffer_len = 0.
 *
 * @path_buffer_len Size of path buffer; if the path of the new
 *    node (including space for the null terminator) exceeds the buffer size,
 *    the path string will be truncated to fit.  The actual path of the
 *    new node in the server will not be affected by the truncation.
 *    The path string will always be null-terminated.
 *
 * @return one of the following codes are returned:
 *   ZOK operation completed successfully
 *   ZNONODE the parent node does not exist.
 *   ZNODEEXISTS the node already exists
 *   ZNOAUTH the client does not have permission.
 *   ZNOCHILDRENFOREPHEMERALS cannot create children of ephemeral nodes.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_create_native(value zh, value path, value val, value acl,
                      value flags, value path_buffer, value path_buffer_len);

CAMLprim value
zkocaml_create_bytecode(value *argv, int argn);

/**
 * Delete a node in zookeeper synchronously.
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
 * @return one of the following values is returned.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADVERSION expected version does not match actual version.
 *   ZNOTEMPTY children are present; node cannot be deleted.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_delete(value zh, value path, value version);

/**
 * Checks the existence of a node in zookeeper synchronously.
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
 * @stat the returned stat value of the node.
 *
 * @return return code of the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_exists(value zh, value path, value watch, value stat);

/**
 * Checks the existence of a node in zookeeper synchronously.
 *
 * This function is similar to zoo_exists except it allows one specify
 * a watcher object rather than a boolean watch flag.
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
 * @stat the return stat value of the node.
 *
 * @return return code of the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_wexists(value zh, value path, value watcher, value watcher_ctx, value stat);

/**
 * Gets the data associated with a node synchronously.
 *
 * @zh the zookeeper handle obtained by a call to zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @buffer the buffer holding the node data returned by the server
 *
 * @stat if not NULL, will hold the value of stat for the path on return.
 *
 * @return return value of the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either in ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_get(value zh, value path, value watch, value buffer, value stat);

/**
 * Gets the data associated with a node synchronously.
 *
 * This function is similar to zoo_get except it allows one specify
 * a watcher object rather than a boolean watch flag.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watcher if non-null, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @watcher_ctx user specific data, will be passed to the watcher callback.
 * Unlike the global context set by \ref zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @buffer the buffer holding the node data returned by the server
 *
 * @stat if not NULL, will hold the value of stat for the path on return.
 *
 * @return return value of the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either in ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_wget_native(value zh, value path, value watcher,
                    value watcher_ctx, value buffer, value stat);

CAMLprim value
zkocaml_wget_bytecode(value *argv, int argn);

/**
 * Sets the data associated with a node. See zoo_set2 function if
 * you require access to the stat information associated with the znode.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @buffer the buffer holding data to be written to the node.
 *
 * @version the expected version of the node. The function will fail if
 * the actual version of the node does not match the expected version. If -1 is
 * used the version check will not take place.
 *
 * @return the return code for the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADVERSION expected version does not match actual version.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_set(value zh, value path, value buffer, value version);

/**
 * Sets the data associated with a node. This function is the same
 * as zoo_set except that it also provides access to stat information
 * associated with the znode.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @buffer the buffer holding data to be written to the node.
 *
 * @version the expected version of the node. The function will fail if
 * the actual version of the node does not match the expected version. If -1 is
 * used the version check will not take place.
 *
 * @stat if not NULL, will hold the value of stat for the path on return.
 *
 * @return the return code for the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADVERSION expected version does not match actual version.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_set2(value zh, value path, value buffer, value version, value stat);

/**
 * Lists the children of a node synchronously.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @strings return value of children paths.
 *
 * @return the return code of the function.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_get_children(value zh, value path, value watch, value strings);

/**
 * Lists the children of a node synchronously.
 *
 * This function is similar to zoo_get_children except it allows one specify
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
 * Unlike the global context set by \ref zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @strings return value of children paths.
 *
 * @return the return code of the function.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_wget_children(value zh, value path, value watcher,
                      value watcher_ctx, value strings);

/**
 * Lists the children of a node and get its stat synchronously.
 *
 * This function is new in version 3.3.0
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watch if nonzero, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @strings return value of children paths.
 *
 * @stat return value of node stat.
 *
 * @return the return code of the function.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_get_children2(value zh, value path, value watch, value strings, value stat);

/**
 * Lists the children of a node and get its stat synchronously.
 *
 * This function is similar to \ref zoo_get_children except it allows one specify
 * a watcher object rather than a boolean watch flag.
 *
 * This function is new in version 3.3.0
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @watcher if non-null, a watch will be set at the server to notify
 * the client if the node changes.
 *
 * @watcher_ctx user specific data, will be passed to the watcher callback.
 * Unlike the global context set by \ref zookeeper_init, this watcher context
 * is associated with the given instance of the watcher only.
 *
 * @strings return value of children paths.
 *
 * @stat return value of node stat.
 *
 * @return the return code of the function.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_wget_children2_native(value zh, value path, value watcher,
                              value watcher_ctx, value strings, value stat);

CAMLprim value
zkocaml_wget_children2_bytecode(value *argv, int argn);

/**
 * Gets the acl associated with a node synchronously.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @acl the return value of acls on the path.
 *
 * @stat returns the stat of the path specified.
 *
 * @return the return code for the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_get_acl(value zh, value path, value acl, value stat);

/**
 * Sets the acl associated with a node synchronously.
 *
 * @zh the zookeeper handle obtained by a call to \ref zookeeper_init
 *
 * @path the name of the node. Expressed as a file name with slashes
 * separating ancestors of the node.
 *
 * @version the expected version of the path.
 *
 * @acl the acl to be set on the path.
 *
 * @return the return code for the function call.
 *   ZOK operation completed successfully
 *   ZNONODE the node does not exist.
 *   ZNOAUTH the client does not have permission.
 *   ZINVALIDACL invalid ACL specified
 *   ZBADVERSION expected version does not match actual version.
 *   ZBADARGUMENTS - invalid input parameters
 *   ZINVALIDSTATE - zhandle state is either ZOO_SESSION_EXPIRED_STATE or ZOO_AUTH_FAILED_STATE
 *   ZMARSHALLINGERROR - failed to marshall a request; possibly, out of memory
 */
CAMLprim value
zkocaml_set_acl(value zh, value path, value version, value acl);

#endif  // _ZKOCAML_H_
