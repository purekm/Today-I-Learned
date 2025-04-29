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


tistory_ID = "rlarudals4949@daum.net"
tistory_Password = "k2090517!"
ID_name = "fortestsele"

def post_to_tistory(title, content):
    
    # 크롬 옵션 설정
    options = webdriver.ChromeOptions()
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-dev-shm-usage')

    # 웹드라이버 경로 설정
    service = Service(executable_path="./chromedriver-win64/chromedriver.exe")
    driver = webdriver.Chrome(service=service, options=options)

    # Tistory 로그인 페이지로 이동
    driver.get("https://www.tistory.com/auth/login")

    time.sleep(2)  # 페이지 로딩 대기

    # 카카오 로그인 버튼 찾기
    kakao_login_button = driver.find_element(By.CLASS_NAME, "btn_login.link_kakao_id")
    kakao_login_button.click()

    time.sleep(2)  # 카카오 로그인 페이지 로딩 대기
    
        # 카카오 로그인 페이지에서 아이디와 비밀번호 입력
    driver.find_element(By.ID, "loginId--1").send_keys(tistory_ID)  # 카카오 아이디 입력
    driver.find_element(By.ID, "password--2").send_keys(tistory_Password)  # 카카오 비밀번호 입력

    # 비밀번호 입력 후 엔터 키를 눌러 로그인 시도
    driver.find_element(By.ID, "password--2").send_keys(Keys.RETURN)

    time.sleep(5)  # 로그인 후 대기

    # 블로그 글 작성 페이지로 이동
    url = f"https://{ID_name}.tistory.com/manage/newpost"
    driver.get(url)

    time.sleep(3)  # 페이지 로딩 대기

    ## HTML 모드로 전환
    
    # 기본모드 버튼 클릭
    try:
        basic_mode_button = driver.find_element(By.ID, "editor-mode-layer-btn-open")
        basic_mode_button.click()
        print("기본모드 버튼 클릭 성공!")
        
        # HTML 모드 버튼이 클릭 가능한 상태일 때까지 기다린 후 클릭
        html_mode_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.ID, "editor-mode-html"))
        )
        html_mode_button.click()
        print("HTML 모드 버튼 클릭 성공!")
        
        # Alert 처리 (알림창이 뜨면 확인 버튼 클릭)
        try:
            alert = WebDriverWait(driver, 5).until(EC.alert_is_present())
            print("Alert 창이 나타났습니다.")
            alert.accept()  # 확인 버튼 클릭 (엔터 키와 동일)
            print("Alert 확인 완료!")
        except Exception as e:
            print("Alert 창 처리 실패:", e)
            
        # # HTML 모드 버튼 클릭 후 엔터 키 입력 (선택 사항)
        # html_mode_button.send_keys(Keys.RETURN)

    except Exception as e:
        print("버튼 클릭 실패:", e)
    
    # 제목 입력
    try:
        title_input = driver.find_element(By.ID, "post-title-inp")  # 제목을 입력할 textarea 요소 찾기
        title_input.send_keys(title)  # 제목 입력
        print("제목 입력 완료!")
    except Exception as e:
        print("제목 입력 실패:", e)

    
    try:
        WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CLASS_NAME, "CodeMirror"))
        )
        time.sleep(1.5)

        driver.execute_script("""
            var content = arguments[0];
            var codeMirrorElement = document.querySelector('.CodeMirror');

            if (!codeMirrorElement || !codeMirrorElement.CodeMirror) {
                console.error("CodeMirror instance not found");
                return;
            }

            var cm = codeMirrorElement.CodeMirror;

            cm.setValue("");  // 먼저 비우고
            cm.focus();

            // 한 글자씩 타이핑한 것처럼 시뮬레이션
            for (let i = 0; i < content.length; i++) {
                let char = content.charAt(i);
                cm.replaceSelection(char);
            }

            cm.save();  // textarea 동기화

            // 이벤트 발생
            var inputField = cm.getInputField();
            inputField.dispatchEvent(new Event('input', { bubbles: true }));
            inputField.dispatchEvent(new Event('change', { bubbles: true }));
        """, content)

        updated_content = driver.execute_script("""
            return document.querySelector('.CodeMirror').CodeMirror.getValue();
        """)
        print("입력된 최종 콘텐츠:", updated_content[:300], "...")

        time.sleep(5)

    except Exception as e:
        print("❌ 콘텐츠 입력 실패:", e)


    ## 글 발행
    # 완료 버튼 클릭
    try:
        complete_button = driver.find_element(By.ID, "publish-layer-btn")  # '완료' 버튼 찾기
        complete_button.click()  # '완료' 버튼 클릭
        print("완료 버튼 클릭 성공!")
    except Exception as e:
        print("완료 버튼 클릭 실패:", e)

    time.sleep(5)  # 게시 후 대기
    
    
    try:
        # '공개 발행' 버튼이 로드될 때까지 대기
        publish_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.ID, "publish-btn"))
        )
        publish_button.click()
        print("✅ '공개 발행' 버튼 클릭 완료!")

        time.sleep(5)  # 발행 완료 대기

    except Exception as e:
        print("❌ '공개 발행' 버튼 클릭 실패:", e)

    # 브라우저 종료
    driver.quit()

# main 함수
if __name__ == "__main__":
    # Flask 서버에서 전달받은 JSON 문자열을 파싱
    input_data = json.loads(sys.argv[1])
    title = input_data.get("title")
    content = input_data.get("content")

    if title and content:
        post_to_tistory(title, content)