import urequests , ujson

#get bitcoin value
'''
_url='http://api.iottweet.com/?userid=000781&key=jka2c5zejnh2&slot0=10.05'
#_url += " HTTP/1.1\r\n"
#_url += "Host: api.iottweet.com\r\n"
#_url += "Connection: keep-alive\r\n\r\n"
_req = urequests.get(_url)
print(_req)
'''
_bct = urequests.get('http://api.coindesk.com/v1/bpi/currentprice.json')
_bct_js = _bct.json()
_us_rate =_bct_js['bpi']['USD']['rate']
_time = _bct_js['time']['updated']
print(_time)
print(_us_rate)

'''
_url = 'https://iapi.bot.or.th/Stat/Stat-ReferenceRate/DAILY_REF_RATE_V1/?'
_url = _url + 'start_period=2017-07-03&end_period=2017-07-07'
_header = {'api-key':'U9G1L457H6DCugT7VmBaEacbHV9RX0PySO05cYaGsm'}
_ex_rate = urequests.get(url=_url,headers=_header)
_rate_js = _ex_rate.json()
print(_rate_js['result']['data']['data_detail'])
'''
