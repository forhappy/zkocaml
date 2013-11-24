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
