class Animator
{
	constructor (startNode, endNode, cycleMax, percent)
	{
		this.originStartNodePos = new pos(startNode.pos.y, startNode.pos.x); // on stock les variables de départ pour faire le swap final
		this.originEndNodePos = new pos(endNode.pos.y, endNode.pos.x);

		this.startNode = startNode; // on stock les node dans des node local
		this.endNode = endNode;

		this.cycleMax = cycleMax; // on stock le nombre de cycle max qu'il faut attendre avant de faire un cycle d'animation
		this.cycle = cycleMax;	// variable qui sera décrémenté à chaque cycle

		this.counter = 0; // ce compteur s'incrémente tant qu'il ne vaut pas lengthAnimation. Animate renvoie false quand ce compteur est au max.
		this.lengthAnimation = 100 / percent;	// length Animation représente un pourcentage de déplacement à effectuer à chaque cycle.

		this.vec = new pos((endNode.pos.y - startNode.pos.y) / this.lengthAnimation, (endNode.pos.x - startNode.pos.x) / this.lengthAnimation); // vecteur à ajouter à chaque cycleMax
	}
};

Animator.prototype.animate = function()
{
	//return false;
	if (this.counter >= this.lengthAnimation)
	{
		this.startNode.pos.y = this.originStartNodePos.y;
		this.startNode.pos.x = this.originStartNodePos.x;

		this.endNode.pos.y = this.originEndNodePos.y;
		this.endNode.pos.x = this.originEndNodePos.x;
		return false;
	}
	if (this.cycle-- > 0)
		return;
	this.startNode.pos.y += this.vec.y;
	this.startNode.pos.x += this.vec.x;
	this.counter++;
	this.cycle = this.cycleMax;
	return true;
}
