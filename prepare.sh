LINUX=$1

remove_ifdef() {
  unifdef -f undef_file.txt -f def_file.txt -DIS_ENABLED=0 $1
}
echo Using Linux kernel from ${LINUX}

rm -rf src tmp
mkdir src tmp
python extract_struct_1.py sched_rt_entity ${LINUX}/include/linux/sched.h tmp/sched_rt_entity.h
python extract_struct_1.py sched_domain    ${LINUX}/include/linux/sched/topology.h tmp/sched_domain.h
python extract_struct_1.py task_struct     ${LINUX}/include/linux/sched.h tmp/task.h
python extract_struct_1.py sched_class     ${LINUX}/kernel/sched/sched.h tmp/sched_class.h
python extract_struct_1.py rt_prio_array   ${LINUX}/kernel/sched/sched.h tmp/rt_prio_array.h
python extract_struct_1.py root_domain     ${LINUX}/kernel/sched/sched.h tmp/root_domain.h
python extract_struct_1.py rt_rq           ${LINUX}/kernel/sched/sched.h tmp/rt_rq.h
python extract_struct_1.py rq              ${LINUX}/kernel/sched/sched.h tmp/rq.h
cp ${LINUX}/kernel/sched/rt.c tmp
remove_ifdef tmp/rt.c              > src/rt.c
remove_ifdef tmp/sched_rt_entity.h > src/sched_rt_entity.h
remove_ifdef tmp/sched_class.h     > src/sched_class.h
remove_ifdef tmp/task.h            > src/task.h
remove_ifdef tmp/rt_rq.h           > src/rt_rq.h
remove_ifdef tmp/rq.h              > src/rq.h
remove_ifdef tmp/root_domain.h     > src/root_domain.h
remove_ifdef tmp/sched_domain.h    > src/sched_domain.h
cp tmp/rt_prio_array.h     src/rt_prio_array.h
cp ${LINUX}/include/linux/pid_types.h          src
cp ${LINUX}/include/linux/sched/prio.h         src
cp ${LINUX}/tools/include/linux/container_of.h src
