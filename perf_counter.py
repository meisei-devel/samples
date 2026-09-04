import time

start_time = time.perf_counter()

time.sleep(1)

end_time = time.perf_counter()

print('time.sleep(1) time = {} Seconds'.format(end_time - start_time))

start_time = time.perf_counter_ns()

time.sleep(2)

end_time = time.perf_counter_ns()

print('time.sleep(2) time = {} MilliSeconds'.format((end_time - start_time) / 1000000))
