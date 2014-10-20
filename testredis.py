import redis

r = redis.StrictRedis(host='localhost', port=12342)
r = redis.StrictRedis(host='localhost', port=6379)
print r.publish('lol', ':1\r\n')