from selenium import webdriver
from selenium.common.exceptions import ElementClickInterceptedException
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
import pyperclip
import time

# Path to Chrome driver
chrome_driver_path = "/Users/heenamatlani/Documents/chromedriver"

# Configure Chrome options
options = webdriver.ChromeOptions()
options.add_experimental_option("detach", True)
driver = webdriver.Chrome(executable_path=chrome_driver_path, options=options)

driver.get('https://products.codeporting.app/convert/ai/java-to-cpp/')
wait = WebDriverWait(driver, 10)

code_editor = wait.until(EC.element_to_be_clickable((By.XPATH, '//*[@id="code-editor"]/div[2]/div[2]/div[2]')))
code_editor.clear()

# Insert Java code into the editor
with open('test.java', 'r') as java_file:
    java_code = java_file.read()

code_editor.send_keys(java_code)
driver.find_element(By.ID, 'btnConvert').click()
copy_code = wait.until(EC.element_to_be_clickable((By.ID, 'btnCopyClipboard')))
while True:
    try:
        copy_code.click()
        break
    except ElementClickInterceptedException:
        # If click is intercepted, wait for a few seconds and then retry
        time.sleep(5)

copied_text = pyperclip.paste()
with open('test.cpp', 'w') as file:
    file.write(copied_text)

time.sleep(5)

code_editor = wait.until(EC.element_to_be_clickable((By.XPATH, '//*[@id="code-editor"]/div[2]/div[2]/div[2]')))
code_editor.clear()

with open('test.cpp', 'r') as cpp_file:
    cpp_code = cpp_file.read()

code_editor.send_keys(cpp_code)

driver.find_element(By.ID, 'btnConvert').click()
copy_code = wait.until(EC.element_to_be_clickable((By.ID, 'btnCopyClipboard')))
while True:
    try:
        copy_code.click()
        break
    except ElementClickInterceptedException:
        time.sleep(5)

copied_text_cpp = pyperclip.paste()
print(copied_text_cpp)
with open('test.cpp', 'w') as file:
    file.write(copied_text_cpp)

driver.quit()
