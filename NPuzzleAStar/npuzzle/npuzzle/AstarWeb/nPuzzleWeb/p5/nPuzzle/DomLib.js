const Dom =
{
	createDiv : (className, parent) =>
	{
		let elem = document.createElement("div");
		elem.setAttribute("class", className);
		parent.appendChild(elem);
		return elem;
	},

	createPara : (className, html, parent) =>
	{
		let elem = document.createElement("p");
		elem.setAttribute("class", className);
		elem.innerHTML = html;
		parent.appendChild(elem);
		return elem;
	},

	createCheckBox : (className, parent, value) =>
	{
		let elem = document.createElement("input");
		elem.setAttribute("class", className);
		elem.setAttribute("type", "checkbox");
		elem.checked = value;
		parent.appendChild(elem);
		return elem;
	},

	createInput : (type, className, parent) =>
	{
		let elem = document.createElement("input");
		elem.setAttribute("type", type);
		elem.setAttribute("class", className);
		parent.appendChild(elem);
		return elem;
	},

	createRange : (minValue, maxValue, parent, className) =>
	{
		let elem = document.createElement("input");
		elem.setAttribute("type", "range");
		elem.max = maxValue;
		elem.min = minValue;
		parent.appendChild(elem);
		parent.setAttribute("class", className);
		return elem;
	},

	createButton : (className, html, parent) =>
	{
		let elem = document.createElement("button");
		elem.setAttribute("class", className);
		elem.innerHTML = html;
		parent.appendChild(elem);
		return elem;
	},
};