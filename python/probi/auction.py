# coding=UTF-8
from selenium import webdriver
from time import sleep
from datetime import datetime, time, timedelta

off = 10
link = 'http://www.ebay.de/itm/Hyundai-L72D-43-cm-17-Zoll-5-4-LCD-Monitor-Silber-/291629370440?hash=item43e6770c48:g:HesAAOSwgyxWUifn'
max_price = 50.0

def wait_time(run_time, offset=0):
	start_time = (datetime.strptime(run_time, '%H:%M:%S') + timedelta(hours=1, seconds=offset)).time()
	while(start_time > datetime.today().time()):
		sleep(1)

def log_in(driver):
	driver.get('http://www.ebay.de/')
	log = driver.find_element_by_link_text('Mein eBay')
	log.click()

	user = driver.find_element_by_id('userid')
	user.send_keys('user')
	
	pasw = driver.find_element_by_id('pass')
	pasw.send_keys('pass')
	pasw.submit()

def wait_precisely(driver, offset):
	end_time = driver.find_element_by_class_name('endedDate').text
	end_time = end_time.replace(' MEZ)', '')
	wait_time(end_time, offset=-off)

def get_ebay_money(driver):
	price = driver.find_element_by_id('prcIsum_bidPrice')
	res = price.text

	res = res.replace('EUR ', '')
	res = res.replace(',', '.')

	return float(res)

def send_offer(driver, offer):
	cell = driver.find_element_by_id('MaxBidId')
	cell.send_keys(offer)

	button = driver.find_element_by_id('bidBtn_btn')
	button.click()

	confirm = driver.find_element_by_css_selector('.fs18 a')
	confirm.click()

web = webdriver.Firefox()
web.implicitly_wait(3)
# log_in(web)
sleep(1)
web.get(link)

# wait_precisely(web, off)
# wait_time('15:33:00', offset=-10)
web.refresh()
money = get_ebay_money(web)
if(money < max_price):
	send_offer(web, money + 1)

sleep(5)
web.quit()
