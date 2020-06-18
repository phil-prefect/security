#!/bin/sh
killall -9 envset_proc
rm -f instance/question1/server/aspect_policy.cfg
rm -f instance/question1/user1/aspect_policy.cfg

yes|cp instance/question1/server/plugin_config.cfg.access instance/question1/server/plugin_config.cfg
yes|cp instance/question1/server/sys_config.cfg.label instance/question1/server/sys_config.cfg
yes|cp instance/question1/server/router_policy.cfg.record instance/question1/server/router_policy.cfg
yes|cp instance/question1/server/aspect_policy.cfg.access instance/question1/server/aspect_policy.cfg

yes|cp instance/question1/user1/sys_config.cfg.record instance/question1/user1/sys_config.cfg
yes|cp instance/question1/user1/router_policy.cfg.record instance/question1/user1/router_policy.cfg
sleep 1

sh run_cube.sh exec_def/_user_server.def &
sleep 1
sh run_cube.sh exec_def/_user_client.def login.msg write.msg read.msg
#sh run_cube.sh exec_def/_user_client.def login.msg
