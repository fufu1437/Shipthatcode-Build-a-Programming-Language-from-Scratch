const test1 = document.getElementById("test1")
const button1 = document.getElementById("button1")
const input1 = document.getElementById("input1")

button1?.addEventListener("click", () => {
	if(test1 && input1) {
		test1.innerText = input1.value // ✅ 读 value，写 innerText
	}
})