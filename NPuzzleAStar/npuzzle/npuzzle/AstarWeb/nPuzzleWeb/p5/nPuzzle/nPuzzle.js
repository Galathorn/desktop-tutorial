class nPuzzle
{
	constructor(sizeGrid)
	{
		this.grid = this.createGrid(sizeGrid);
		this.size = sizeGrid;
	}
}

function fillGrid(grid, size)
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
		console.log("y = ", y, " x = ", x, "value = ", grid[y][x].value);
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
	fillGrid(grid, size);
	return grid;
}

nPuzzle.prototype.print = function(color)
{
	stroke(color.r, color.g, color.b);
	fill(color.r, color.g, color.b);
	for (let y = 0; y < this.size; ++y)
		for (let x = 0; x < this.size; ++x)
			rect(render.spaceX / 4 + x * render.squareWidth + (x * render.spaceX / 4), render.spaceX / 4 +  y * render.squareHeight + (y * render.spaceY / 4), render.squareWidth, render.squareHeight);
	stroke(0);
	fill(0);
}

class Node
{
	constructor (_y, _x, value)
	{
		this.pos = new pos(_y, _x);
		this.gCost = 0;
		this.hCost = 0;
		this.value = 0;
	}
};

Node.prototype.fCost = function()
{
	return this.gCost + this.hCost;
}

class pos
{
	constructor(_y, _x)
	{
		this.y = _y;
		this.x = _x;
	}
};

// définition des variables environnementales
let color;
let npuzzle;
let path = null;
let dest;

let size = {};
size.width = 900;
size.height = 900;
size.squareSize = 4;

let canvas; 
let render;

function generateNewEnvironment()
{
	canvas = createCanvas(size.width, size.height);
	canvas.position(window.innerWidth * 0.25, window.innerHeight * 0.07);
}

function setupRender()
{
	render = {};
	render.spaceX = size.width * 0.025;
	render.spaceY = size.height * 0.025;
	render.squareWidth = (size.width - render.spaceX) / size.squareSize;
	render.squareHeight = (size.height - render.spaceY) / size.squareSize;
}

function setupNpuzzle()
{
	npuzzle = new nPuzzle(size.squareSize);
}

function setupColor(r,g,b)
{
	color = {};
	color.r = r;
	color.g = g;
	color.b = b;
}

function setup() 
{
	frameRate(60);
	setupColor(0, 0, 0);
	setupRender();
	generateNewEnvironment();
	setupNpuzzle();
}
function draw()
{
	background(240);
	npuzzle.print(color);
}
