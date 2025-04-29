import json
import sys
import time
import traceback
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys


naver_ID = "rudals4349"
naver_Password = "05971550aa!"

# 1. JSON 데이터 받아오기
data = json.loads(sys.argv[1])
title = data["title"]
content = data["content"]
image_url = data.get("image_url", "")

# 2. 이미지 삽입
if image_url:
    content += f'\n\n<img src="{image_url}" alt="이미지">'
    
# 3. 크롬 설정
options = webdriver.ChromeOptions()
# options.add_argument('--headless')  # 개발 중엔 주석
options.add_argument('--no-sandbox')
options.add_argument('--disable-dev-shm-usage')

service = Service(executable_path="./chromedriver-win64/chromedriver.exe")
driver = webdriver.Chrome(service=service, options=options)

try:
    # 4. 네이버 로그인
    driver.get("https://nid.naver.com/nidlogin.login")
    time.sleep(2)
    driver.execute_script(f"document.getElementById('id').value='{naver_ID}'")
    driver.execute_script(f"document.getElementById('pw').value='{naver_Password}'")
    driver.find_element(By.ID, 'log.login').click()
    time.sleep(4)
    
    # ## 쓰고 있던 글이 있으면 취소하고 작성
    # try:
    #     cancel_button = WebDriverWait(driver, 3).until(
    #         EC.element_to_be_clickable((By.CSS_SELECTOR, "button.se-popup-button.se-popup-button-cancel"))
    #     )
    #     cancel_button.click()
    #     time.sleep(1)  # 팝업 사라질 시간 대기
    # except:
    #     print("⚠️ 취소 버튼 없음 또는 이미 닫힘 상태")
        
    # 5. 블로그 글쓰기 페이지로 이동
    driver.get(f"https://blog.naver.com/{naver_ID}?Redirect=Write")
    time.sleep(4)

    # 6. 제목 입력
    ## iframe으로 진입
    WebDriverWait(driver, 10).until(
    EC.frame_to_be_available_and_switch_to_it((By.ID, "mainFrame"))
)
    ## 1. placeholder 클릭 (포커스 주기)
    placeholder = WebDriverWait(driver, 10).until(
         EC.element_to_be_clickable((By.CSS_SELECTOR, "span.se-placeholder.__se_placeholder.se-ff-nanumgothic.se-fs32"))
    )
    driver.execute_script("arguments[0].click();", placeholder)
    
    time.sleep(0.5)  # 포커스 생성 대기
    
    print(driver.execute_script("return window.location.href"))
    ## 2. 실제 제목 입력란에 입력
    title_box = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.CSS_SELECTOR, "span.se-ff-nanumgothic.se-fs32.__se-node"))
    )

    ActionChains(driver) \
        .move_to_element(title_box) \
        .click() \
        .key_down(Keys.CONTROL).send_keys("a").key_up(Keys.CONTROL) \
        .send_keys(title) \
        .perform()
        
    
    # ✅ 7. 본문 입력
    content_box = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.CSS_SELECTOR, "span.__se-node.se-fs15"))
    )
    ActionChains(driver) \
        .move_to_element(content_box) \
        .click() \
        .key_down(Keys.CONTROL).send_keys("a").key_up(Keys.CONTROL) \
        .send_keys(content) \
        .perform()
    
    # ✅ 8. 발행 버튼 클릭
    publish_button = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.CSS_SELECTOR, "button.publish_btn__m9KHH"))
    )
    driver.execute_script("arguments[0].scrollIntoView(true);", publish_button)
    driver.execute_script("arguments[0].click();", publish_button)
    
    # ✅ 9. 발행 확인 버튼 (모달 안)
    confirm_button = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.CSS_SELECTOR, "button.confirm_btn__WEaBq"))
    )
    driver.execute_script("arguments[0].scrollIntoView(true);", confirm_button)
    driver.execute_script("arguments[0].click();", confirm_button)

    print("✅ 블로그 최종 발행 완료!")

except Exception as e:
    print("❌ 오류 발생:", str(e))
    traceback.print_exc()

finally:
    # driver.quit()
    pass
