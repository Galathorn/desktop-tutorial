class Scrambler
{
	constructor(amount)
	{
		this.all	 = ["UP","DOWN","RIGHT","LEFT"];
		this.noUp	 = ["RIGHT","LEFT"];
		this.noDown	 = ["RIGHT","LEFT"];
		this.noRight = ["UP","DOWN"];
		this.noLeft	 = ["UP","DOWN"];

		this.lastMove = null;

		this.max = amount;		// variable indiquant le nombre maximum de mouvement que le npuzzle va executer pour le scrambler
		this.isOn = true; // boolean indiquant si le npuzzle à été au moins scramble une fois.
		this.countMove = 0;
	}
}

Scrambler.prototype.applyMove = function(nextMove)
{
	if (nextMove == this.lastMove)
		return false;
	if (nextMove == "UP")
		return npuzzle.Up();
	else if (nextMove == "DOWN")
		return npuzzle.Down();
	else if (nextMove == "RIGHT")
		return npuzzle.Right();
	else if (nextMove == "LEFT")
		return npuzzle.Left();
}

Scrambler.prototype.oneRandomMove = function()
{
	let m = null;
	if (this.isOn == false)
		return;
	this.countMove = (this.countMove + 1) % this.max;
	while (1)
	{
		if (this.lastMove == "UP")
			m = this.noUp[getRandomInt(2)];
		else if (this.lastMove == "RIGHT")
			m = this.noRight[getRandomInt(2)];
		else if (this.lastMove == "DOWN")
			m = this.noDown[getRandomInt(2)];
		else if (this.lastMove == "LEFT")
			m = this.noLeft[getRandomInt(2)];
		else if (this.lastMove == null)
			m = this.all[getRandomInt(4)];
		let ret = this.applyMove(m);
		if (ret == true)
			break ;
	}
	if (this.countMove == 0)
		this.isOn = false;
//	console.log(m);
	this.lastMove = m;
}

