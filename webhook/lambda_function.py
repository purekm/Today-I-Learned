import json
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys

# Tistory 계정 설정 (보안상 실제 배포 땐 환경변수로 분리 권장)
tistory_ID = "rlarudals4949@daum.net"
tistory_Password = "k2090517!"
ID_name = "fortestsele"

def post_to_tistory(title, content):
    # Lambda용 Chrome 옵션 설정
    options = webdriver.ChromeOptions()
    options.binary_location = "/opt/bin/headless-chromium"
    options.add_argument('--headless')
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-dev-shm-usage')
    options.add_argument('--single-process')
    options.add_argument('--disable-gpu')

    # 드라이버 서비스 설정
    service = Service("/opt/bin/chromedriver")
    driver = webdriver.Chrome(service=service, options=options)

    try:
        # Tistory 로그인
        driver.get("https://www.tistory.com/auth/login")
        time.sleep(2)

        kakao_login_button = driver.find_element(By.CLASS_NAME, "btn_login.link_kakao_id")
        kakao_login_button.click()
        time.sleep(2)

        driver.find_element(By.ID, "loginId--1").send_keys(tistory_ID)
        driver.find_element(By.ID, "password--2").send_keys(tistory_Password)
        driver.find_element(By.ID, "password--2").send_keys(Keys.RETURN)
        time.sleep(5)

        # 새 글 작성 페이지로 이동
        driver.get(f"https://{ID_name}.tistory.com/manage/newpost")
        time.sleep(3)

        # HTML 모드 진입
        try:
            driver.find_element(By.ID, "editor-mode-layer-btn-open").click()
            html_mode_button = WebDriverWait(driver, 10).until(
                EC.element_to_be_clickable((By.ID, "editor-mode-html"))
            )
            html_mode_button.click()

            try:
                alert = WebDriverWait(driver, 5).until(EC.alert_is_present())
                alert.accept()
            except:
                pass
        except:
            pass

        # 제목 입력
        driver.find_element(By.ID, "post-title-inp").send_keys(title)

        # 콘텐츠 입력 (HTML 모드)
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "CodeMirror")))
        time.sleep(1.5)

        driver.execute_script("""
            var content = arguments[0];
            var codeMirrorElement = document.querySelector('.CodeMirror');
            if (!codeMirrorElement || !codeMirrorElement.CodeMirror) return;
            var cm = codeMirrorElement.CodeMirror;
            cm.setValue("");
            cm.focus();
            for (let i = 0; i < content.length; i++) {
                cm.replaceSelection(content.charAt(i));
            }
            cm.save();
            var inputField = cm.getInputField();
            inputField.dispatchEvent(new Event('input', { bubbles: true }));
            inputField.dispatchEvent(new Event('change', { bubbles: true }));
        """, content)

        time.sleep(5)

        # 완료 → 공개 발행
        driver.find_element(By.ID, "publish-layer-btn").click()
        publish_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.ID, "publish-btn"))
        )
        publish_button.click()
        time.sleep(5)

    finally:
        driver.quit()


def lambda_handler(event, context):
    title = event.get("title", "기본 제목")
    content = event.get("content", "기본 콘텐츠입니다.")

    try:
        post_to_tistory(title, content)
        return {
            "statusCode": 200,
            "body": json.dumps("Tistory 글 발행 성공")
        }
    except Exception as e:
        return {
            "statusCode": 500,
            "body": json.dumps(f"실패: {str(e)}")
        }
