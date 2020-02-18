class nPuzzle
{
	constructor(sizeGrid)
	{
		this.id = 0;
		this.grid = null;
		this.size = sizeGrid;
		this.empty = null;
		this.gCost = 0; // s'incrémente de 1 à chaque fois que l'on test une nouvelle possibilité.
		this.parent = null;
		this.defMove = null; // move qui justifie la présence de cet instance du puzzle.
	}
}

nPuzzle.prototype.copyData = function()
{
	let copy = stackNpuzzle.pop();
	if (copy == null)
		return null;
	for (let y = 0; y < this.size; ++y)
		for (let x = 0; x < this.size; ++x)
		{
			this.grid[y][x].copyData(copy.grid[y][x]);
			if (copy.grid[y][x].value == 0)
				copy.empty = copy.grid[y][x];
		}
	copy.id = this.id + 1;
	copy.defMove = null;
	return copy;
}

// cette fonction sera appelé à chaque fois que l'on checkera les voisins de la node en cours. on créera ainsi une copy du npuzzle actuel.
nPuzzle.prototype.copy = function()
{
	let copy = new nPuzzle(this.size);
	copy.grid = new Array();
	for (let y = 0; y < this.size; ++y)
	{
		copy.grid[y] = new Array();
		for (let x = 0; x < this.size; ++x)
		{
			copy.grid[y][x] = this.grid[y][x].copy();
			if (copy.grid[y][x].value == 0)
				copy.empty = copy.grid[y][x];
		}
	}
	copy.id = this.id + 1;
	return copy;
}

// fonction qui va parcourir chaque élément dans la grille et calculer la distance entre sa position actuel et la position qu'elle devrait avoir au final.
// chacune de ses valeur sera additionné pour former le hCost de l'état du Npuzzle en lui même.
nPuzzle.prototype.hCost = function()
{
	let cost = 0;
	let linear = 0;
	for (let y = 0; y < this.size; ++y)
		for (let x = 0; x < this.size; ++x)
		{
			if (this.grid[y][x].value != 0)
				cost += this.grid[y][x].distance();

			if (this.grid[y][x].pos.y == this.grid[y][x].truePos.y || this.grid[y][x].pos.x == this.grid[y][x].truePos.x) // la node possède l'une de ses deux coordonné avec sa véritable pos
				if (this.grid[y][x].pos.y != this.grid[y][x].truePos.y || this.grid[y][x].pos.x != this.grid[y][x].truePos.x) // mais l'une des deux au moins n'est pas pareil
					if (this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].truePos.y == this.grid[y][x].pos.y || this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].truePos.x == this.grid[y][x].pos.x)
					{
						if (this.grid[y][x].value == 0 || this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].value == 0)
							continue;
						if (this.grid[y][x].distance() > 1 || this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].distance() > 1)
							continue;
						if (this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].truePos.y == this.grid[y][x].pos.y && this.grid[y][x].pos.y == this.grid[y][x].truePos.y)
						{
							linear++;
						//	console.log(this.grid[y][x].value, this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].value);
						//	console.log("linear man !");
						}
						else if (this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].truePos.x == this.grid[y][x].pos.x && this.grid[y][x].pos.x == this.grid[y][x].truePos.x)
						{
						//	console.log(this.grid[y][x].value, this.grid[this.grid[y][x].truePos.y][this.grid[y][x].truePos.x].value);
							linear++;
						//	console.log("linear man !");
						}
					}
						
		}
	linear *= 2;
	cost += linear;
	return cost;
}

// Fonction qui va renvoyer l'addition de hCost et de gCost du npuzzle en cours.
nPuzzle.prototype.fCost = function()
{
	return this.hCost() + this.gCost;
}

// fonction qui sera appelé par le setup du programme car il va placer au bon endroit chaque valeur de chaque Node.
nPuzzle.prototype.fillGrid = function(grid, size)
{
	let goalValue = size * size;
	let array = ["RIGHT","DOWN","LEFT","UP"];
	let dir = 0;
	let countDir = size;
	let count = 0;
	let y = 0;
	let x = 0;
	let countdown = 1;
	while (++count <= goalValue)
	{
		grid[y][x].value = count == goalValue ? 0 : count;
		countDir--;
		if (array[dir] == "RIGHT")
			countDir == 0 ? y++ : x++;
		else if (array[dir] == "DOWN")
			countDir == 0 ? x-- : y++;
		else if (array[dir] == "LEFT")
			countDir == 0 ? y-- : x--;
		else if (array[dir] == "UP")
			countDir == 0 ? x++ : y--;
		if (countDir == 0)
		{
			countdown++;
			if (countdown == 2)
			{
				countdown = 0;
				size--;
			}
			dir = (dir + 1) % array.length;
			countDir = size;
		}
	}
}

// swap pos of two nodes
nPuzzle.prototype.swapNode = function (grid, y, x, emptyY, emptyX)
{
	let tmpNode = grid[y][x];
	grid[y][x] = grid[emptyY][emptyX];
	grid[emptyY][emptyX] = tmpNode;

	let tmpPos = new pos(grid[y][x].pos.y, grid[y][x].pos.x);
	grid[y][x].pos.y = grid[emptyY][emptyX].pos.y;
	grid[y][x].pos.x = grid[emptyY][emptyX].pos.x;
	grid[emptyY][emptyX].pos.y = tmpPos.y;
	grid[emptyY][emptyX].pos.x = tmpPos.x;
}

// cette fonction va initialiser un animator afin d'éxécuter la transition d'un état vers un autre.
nPuzzle.prototype.swapNodeAnimator = function (grid, y, x, emptyY, emptyX)
{
	animator = new Animator(grid[y][x], grid[emptyY][emptyX], CYCLE_MAX, PERCENT);
}

nPuzzle.prototype.Up = function(notAnimated = null)
{
	if (this.empty.pos.y + 1 >= this.size)
		return false;
	let node = this.grid[this.empty.pos.y + 1][this.empty.pos.x];
	if (animationAreOn == false)
		this.swapNode(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
	else
		this.swapNodeAnimator(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
//	console.log("UP");
	return true;
}

nPuzzle.prototype.Down = function(notAnimated = null)
{
	if (this.empty.pos.y - 1 < 0)
		return false;
	let node = this.grid[this.empty.pos.y - 1][this.empty.pos.x];
	if (animationAreOn == false)
		this.swapNode(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
	else
		this.swapNodeAnimator(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
//	console.log("DOWN");
	return true;
}

nPuzzle.prototype.Right = function(notAnimated = null)
{
	if (this.empty.pos.x - 1 < 0)
		return false;
	let node = this.grid[this.empty.pos.y][this.empty.pos.x - 1];
	if (animationAreOn == false)
		this.swapNode(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
	else
		this.swapNodeAnimator(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
//	console.log("RIGHT");
	return true;
}

nPuzzle.prototype.Left = function(notAnimated = null)
{
	if (this.empty.pos.x + 1 >= this.size)
		return false;
	let node = this.grid[this.empty.pos.y][this.empty.pos.x + 1];
	if (animationAreOn == false)
		this.swapNode(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
	else
		this.swapNodeAnimator(this.grid, node.pos.y, node.pos.x, this.empty.pos.y, this.empty.pos.x);
//	console.log("LEFT");
	return true;
}

nPuzzle.prototype.applyMove = function(y, x)
{
	if (y < 0 || x < 0 || y >= this.size || x >= this.size || this.grid[y][x].value == 0)
		return;
	let emptyPos = null;

	if (x + 1 < this.size && this.grid[y][x + 1].value == 0)
		emptyPos = new pos(y, x + 1);
	else if (x - 1 >= 0 && this.grid[y][x - 1].value == 0)
		emptyPos = new pos(y, x - 1);
	else if (y + 1 < this.size && this.grid[y + 1][x].value == 0)
		emptyPos = new pos(y + 1, x);
	else if (y - 1 >= 0 && this.grid[y - 1][x].value == 0)
		emptyPos = new pos(y - 1, x);

	if (emptyPos == null)
	{
		console.log("INVALID EMPTY POS");
		return;
	}
	animationAreOn == true ? this.swapNodeAnimator(this.grid, y, x, emptyPos.y, emptyPos.x) : this.swapNode(this.grid, y, x, emptyPos.y, emptyPos.x)
}

nPuzzle.prototype.createGrid = function(size)
{
	let v = 0;
	let grid = new Array();
	for (let y = 0; y < size; ++y)
	{
		grid[y] = Array();
		for (let x = 0; x < size; ++x)
		{
			v++;
			grid[y][x] = new Node(y, x, 0);
		}
	}
	return grid;
}

nPuzzle.prototype.fillEmpty = function()
{
	for (let y = 0; y < this.size; ++y)
		for (let x = 0; x < this.size; ++x)
			if (this.grid[y][x].value == 0)
				return this.grid[y][x];
}

nPuzzle.prototype.print = function(color)
{
	stroke(color.r, color.g, color.b);
	fill(color.r, color.g, color.b);
	textSize(35 - npuzzle.size * 1.5);
	for (let y = 0; y < this.size; ++y)
		for (let x = 0; x < this.size; ++x)
		{
			if (this.grid[y][x].value == 0)
				continue;
			let offsetX = render.spaceX / (this.size + 1);
			let offsetY = render.spaceY / (this.size + 1);
			let xPos = offsetX + this.grid[y][x].pos.x * render.squareWidth + this.grid[y][x].pos.x * offsetX;
			let yPos = offsetY + this.grid[y][x].pos.y * render.squareHeight + this.grid[y][x].pos.y * offsetY;

			stroke(color.r, color.g, color.b);
			fill(color.r, color.g, color.b);
			rect(xPos, yPos, render.squareWidth, render.squareHeight);

			stroke(255, 255, 255, 255);
			fill(255, 255, 255, 255);
			text(this.grid[y][x].value, xPos + render.squareWidth / 2 - offsetX * 4, yPos + render.squareHeight / 2);
		}
	stroke(0);
	fill(0);
}
