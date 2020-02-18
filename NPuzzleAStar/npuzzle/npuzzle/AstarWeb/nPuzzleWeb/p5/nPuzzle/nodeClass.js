class Node
{
	constructor (_y, _x, _value)
	{
		this.pos = new pos(_y, _x);		// la position est une position 'relative' c'est � dire qu'elle changera en cours de parti en fonction des d�placements de la node.
		this.truePos = new pos(_y, _x); // TruePos est une variable indiquant la v�ritable position de la node en cours. Elle est assign� une fois en d�but de partie puis jamais touch� ensuite.
		this.value = _value;			// value repr�sente la valeur contenue dans la case en cours.
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
