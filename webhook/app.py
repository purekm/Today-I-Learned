from flask import Flask, request, jsonify
import subprocess
import json

python_path = r"C:\Python313\python.exe"
app = Flask(__name__)


@app.route('/tistory/post', methods=['POST'])
def post_tistory_blog():
    print("===== Raw Body =====")
    print(request.data.decode("utf-8"))  # 이 줄이 핵심!
    print("===== Headers =====")
    print(request.headers)

    data = request.get_json(force=True)
    title = data.get("title")
    content = data.get("content")

    # Tistory 블로그 포스팅을 위한 셀레니움 스크립트 실행
    json_str = json.dumps({
        "title": title,
        "content": content
    })

    # subprocess로 post_to_tistory.py 실행
    subprocess.run(["python", "post_to_tistory.py", json_str])

    return jsonify({"status": "posted"}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
