ZkOCaml
=======

Apache zookeeper client binding for OCAML programming language.

# ZkOCaml: an one-minute introduction for beginners #
ZkOCaml is the first(as far as I know) Ocaml binding for Apache Zookeeper. If you are wondering what is Apache Zookeeper, please visit the [zookeeper official website](http://zookeeper.apache.org/ "Apache ZooKeeper") to get more information about it, hereinafter is an one-sentence description that can inform of you what is apache zookeeper: 

> [ZooKeeper](http://zookeeper.apache.org/ "Apache ZooKeeper") is a high-performance coordination service for distributed applications. It exposes common services - such as naming, configuration management, synchronization, and group services - in a simple interface so you don't have to write them from scratch. You can use it off-the-shelf to implement consensus, group management, leader election, and presence protocols.

ZkOCaml provides a complete API binding of Ocaml for apache zookeeper(hereinafter referred to as `zookeeper`), including synchronous and asynchronous interface as well as some useful auxiliary APIs. That is, you may create/delete/get/update(CRUD) a zookeeper node(ZNode) in Ocaml language synchronously and/or asynchronously without any pains.

# How to build ZkOCaml #
## Prepare to build ZkOCaml ##
First of all, you have to get ZkOCaml source code from github:

    ~$git clone git@github.com:forhappy/zkocaml.git

## Dependencies ##
ZkOCaml has no other dependencies except for zookeeper c API implementation, which usually resides in `zookeeper-X.Y.Z/src/c`, hence you need to install zookeeper c API at first.

# Install ZkOCaml #

all you have to do is just a `make` to compile ZkOCaml:

    ZkOCaml$ make

If you want to install ZkOCaml into your system after you have compiled ZkOCaml, you need to `make install`(as root):

    ZkOCaml$ make install

# Getting started in 5 minutes #
## Examples ##


# API specification #
See docs/* for more details about ZkOCaml's API specification.

# License #
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements. See the NOTICE file
distributed with this work for additional information
regarding copyright ownership. The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

