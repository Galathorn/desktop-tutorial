class Node
{
	constructor (_y, _x, _value)
	{
		this.pos = new pos(_y, _x);		// la position est une position 'relative' c'est à dire qu'elle changera en cours de parti en fonction des déplacements de la node.
		this.truePos = new pos(_y, _x); // TruePos est une variable indiquant la véritable position de la node en cours. Elle est assigné une fois en début de partie puis jamais touché ensuite.
		this.value = _value;			// value représente la valeur contenue dans la case en cours.
	}
};

Node.prototype.distance = function()
{
	return dist(this.pos.y, this.pos.x, this.truePos.y, this.truePos.x);
}

Node.prototype.copyData = function(node)
{
	node.truePos.y = this.truePos.y;
	node.truePos.x = this.truePos.x;

	node.pos.y = this.pos.y;
	node.pos.x = this.pos.x;

	node.value = this.value;
}

Node.prototype.copy = function()
{
	let node = new Node(this.pos.y, this.pos.x, this.value);
	node.truePos.y = this.truePos.y;
	node.truePos.x = this.truePos.x;
	return node;
}
