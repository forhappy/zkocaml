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

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/signals.h>

#include <zookeeper/zookeeper.h>

/**
 * The zkocaml_handle_t wraps a zookeeper connection handle
 * which indicates a zookeeper session that corresponds to that handle.
 */
typedef struct zkocaml_handle_s_ {
  zhandle_t *handle;
} zkocaml_handle_t;

/**
 * The zkocaml_watcher_context_t wraps a zookeeper watcher context.
 */
typedef struct zkocaml_watcher_context_s_ {
  void *watcher_ctx;
  value watcher_callback;
} zkocaml_watcher_context_t;

/**
 * The zkocaml_completion_context_t wraps a zookeeper completion data.
 */
typedef struct zkocaml_completion_context_s_ {
  void *data;
  value completion_callback;
} zkocaml_completion_context_t;

/**
 * The ZOO_EPHEMERAL_AUX wraps zookeeper event type.
 */
typedef enum ZOO_EVENT_AUX {
  ZOO_CREATED_EVENT_AUX,
  ZOO_DELETED_EVENT_AUX,
  ZOO_CHANGED_EVENT_AUX,
  ZOO_CHILD_EVENT_AUX,
  ZOO_SESSION_EVENT_AUX,
  ZOO_NOTWATCHING_EVENT_AUX
} ZOO_EVENT_AUX;

/**
 * The ZOO_STATE_AUX wraps zookeeper connection state.
 */
typedef enum ZOO_STATE_AUX {
  ZOO_EXPIRED_SESSION_STATE_AUX,
  ZOO_AUTH_FAILED_STATE_AUX,
  ZOO_CONNECTING_STATE_AUX,
  ZOO_ASSOCIATING_STATE_AUX,
  ZOO_CONNECTED_STATE_AUX
} ZOO_STATE_AUX ;

/**
 * The ZOO_PERM_AUX wraps zookeeper ACL constants.
 */
typedef enum ZOO_PERM_AUX {
  ZOO_PERM_READ_AUX,
  ZOO_PERM_WRITE_AUX,
  ZOO_PERM_CREATE_AUX,
  ZOO_PERM_DELETE_AUX,
  ZOO_PERM_ADMIN_AUX,
  ZOO_PERM_ALL_AUX
} ZOO_PERM_AUX;

/**
 * The ZOO_CREATE_FLAG_AUX wraps zookeeper creation flag.
 */
typedef enum ZOO_CREATE_FLAG_AUX {
  ZOO_EPHEMERAL_AUX,
  ZOO_SEQUENCE_AUX
} ZOO_CREATE_FLAG_AUX;

#endif  // _ZKOCAML_H_
