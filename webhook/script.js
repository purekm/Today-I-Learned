document.getElementById("runWebhook").addEventListener("click", function() {
    fetch("https://hook.eu2.make.com/fsake0cjw0wfwy2kxox3wf5uwyx1gbak", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            message: "버튼이 클릭됨!",
            user: "사용자1",
            timestamp: new Date().toISOString()
        })
    })
    .then(response => response.json())  // 이제 JSON 응답을 받으므로 json() 사용 가능
    .then(data => {
        console.log("Make 응답:", data);
        alert("응답: " + data.message);
    })
    .catch(error => console.error("오류 발생:", error));
});

