// définition des variables environnementales

let path = null;
let trail = null;
let pathIsDone = false;

let size = {};
size.width = 900;
size.height = 900;

let currentMode = "Pathfinder";
let tmpCurrentMode = currentMode;
let percentObstacles = 10;
let tmpPercentObstacles = percentObstacles;
let amount = 75;
let tmpAmount = amount;
// declaration de tout mes outils

// classe NODE ainsi que ses méthodes
class Node
{
	constructor(_y, _x, _value)
	{
		this.value = _value;
		this.pos = new pos(_y, _x);
		this.gCost = 0;
		this.hCost = 0;
		this.parent = null;
	}
};

Node.prototype.fCost = function()
{
	return this.gCost + this.hCost;
}


// fin de la classe NODE
// classe POS
class pos
{
	constructor(_y, _x)
	{
		this.y = _y;
		this.x = _x;
	}
};
// fin de la class POS
// initialisation des variables environnementales

let canvas; 
let grid;
let render;

let dest;
let player = {};
player.cycleMax = 0;
player.cycle = player.cycleMax;
player.value = 2;
player.pathIndex = 0;

player.pos = new pos(1, 1);

let cycleTrailMax = player.cycleMax / 2;
let cycleTrail = cycleTrailMax;

let pathKey = {};
pathKey.keyCode = 80;
pathKey.letter = 'p';
let brushKey = {};
brushKey.keyCode = 66;
brushKey.letter = 'e';
let wallKey = {};
wallKey.keyCode = 87;
wallKey.letter = 'w';

let mode = pathKey.letter;



// fonctions de setup d'environements qui sont appelé lors de la générations d'une nouvelle grille ainsi qu'au lancement d'une nouvelle page.
function setupRender()
{
	let render = {};
	render.columnWidth = size.width / grid.x;
	render.columnHeight = size.height;

	render.lineWidth = size.width;
	render.lineHeight = size.height / grid.y;
	return render;
}

function setupGrid()
{
	let grid = {};
	grid.x = amount;
	grid.y = amount;

	grid.array = new Array(grid.y);
	for(let y = 0; y < grid.y; y++)
	{
		grid.array[y] = new Array(grid.x);
		for (let x = 0; x < grid.x; ++x)
			grid.array[y][x] =  new Node(y, x, random(0, 100) < percentObstacles ? 1 : 0);
	}
	
	grid.array[player.pos.y][player.pos.x].value = player.value;
	return grid;
}

function generateNewGrid()
{

	amount = tmpAmount;
	percentObstacles = tmpPercentObstacles;
	trail = null;
	path = null;
	pathIsDone = false;

	canvas = createCanvas(size.width, size.height);
	canvas.position(window.innerWidth * 0.25, window.innerHeight * 0.07);

	grid = setupGrid();
	render = setupRender();
}


// fonctions algorithmique (coeur du programme)
function getNeighbours(_grid, currentNodePos)
{
	let list = new Array();
	if (currentNodePos.x - 1 >= 0 && _grid.array[currentNodePos.y][currentNodePos.x - 1].value == 0)
		list.push(_grid.array[currentNodePos.y][currentNodePos.x - 1]);
	if (currentNodePos.x + 1 < amount && _grid.array[currentNodePos.y][currentNodePos.x + 1].value == 0)
		list.push(_grid.array[currentNodePos.y][currentNodePos.x + 1]);
	if (currentNodePos.y - 1 >= 0 && _grid.array[currentNodePos.y - 1][currentNodePos.x].value == 0)
		list.push(_grid.array[currentNodePos.y - 1][currentNodePos.x]);
	if (currentNodePos.y + 1 < amount && _grid.array[currentNodePos.y + 1][currentNodePos.x].value == 0)
		list.push(_grid.array[currentNodePos.y + 1][currentNodePos.x]);

	return list;
}

function aStar(_grid, startPos, endPos)
{
	let openSet = new Array();
	let closedSet = new Array();
	openSet.push(_grid.array[startPos.y][startPos.x]);
	while (openSet.length > 0)
	{
		let current = openSet[0];
		for (let i = 1; i < openSet.length; ++i)
		{
			if (openSet[i].fCost() < current.fCost() || openSet[i].fCost() == current.fCost() && openSet[i].hCost < current.hCost)
				current = openSet[i];
		}
		openSet.splice(openSet.indexOf(current), 1);
		closedSet.push(current);
		if (current.pos.y == endPos.y && current.pos.x == endPos.x)
		{
			let _path = [];
			while (current.pos.y != startPos.y || current.pos.x != startPos.x)
			{
				_path.push(current);
				current = current.parent;
			}
			_path.push(current);
			reverse(_path);
			return _path; // reconstruire le chemin.
		}
		let neighbours = getNeighbours(_grid, current.pos);
		for (let i = 0; i < neighbours.length; ++i)
		{
			if ( closedSet.includes(neighbours[i]) )
				continue;
			let newMovementCostToNeighbour = current.gCost + dist(current.pos.x, current.pos.y, neighbours[i].pos.x, neighbours[i].pos.y);
			if (newMovementCostToNeighbour < neighbours[i].gCost || !openSet.includes(neighbours[i]))
			{
				neighbours[i].gCost = newMovementCostToNeighbour;
				neighbours[i].hCost = dist(neighbours[i].pos.x, neighbours[i].pos.y, endPos.x, endPos.y);
				neighbours[i].parent = current;
				if (!openSet.includes(neighbours[i]))
					openSet.push(neighbours[i]);
			}
		}
	}
}

////////////////////////////////////////////////


// fonctions concernant IDA*

// cette fonction renvoi la distance entre deux nodes
function getDistance(startNode, endNode)
{
	return dist(startNode.pos.x, startNode.pos.y, endNode.pos.x, endNode.pos.y);
}

function isGoal(currentNode, endNode)
{
	if (currentNode.pos.y == endNode.pos.y && currentNode.pos.x == endNode.pos.x)
		return true;
	return false;
}
let indexSearch = 0;
function search(_path, g, bound, destNode, _grid)
{
	indexSearch++;
	let cur_node = _path[_path.length - 1];
	let f = g + getDistance(cur_node, destNode);
	if (f > bound)
		return f;
	if (isGoal(cur_node, destNode) == true)
		return 0;
	let min = Infinity;
	let neighbours = getNeighbours(_grid, cur_node.pos);
	for (let i = 0; i < neighbours.length; ++i)
	{
		if (_path.includes(neighbours[i]))
			continue;
		_path.push(neighbours[i]);
		let t = search(_path, g + getDistance(cur_node, neighbours[i]), bound, destNode, _grid);
		if (t == 0)
			return 0;
		if (t < min)
			min = t;
		_path.pop();
	}
	return min;
}

function idAstar(_grid, startPos, endPos)
{
	let _path = new Array();
	let current = _grid.array[startPos.y][startPos.x];
	let destNode = _grid.array[endPos.y][endPos.x];
	let bound = getDistance(current, destNode);
	let counter = 0;
	_path.push(current);
	while (1)
	{
		counter++;
		let t = search(_path, 0, bound, destNode, _grid);
		if (t == 0)
			break;
		if (t == -1)
		{
			_path = null;
			break;
		}
		bound = t;
	}
	console.log("counter = " , counter);
	console.log("indexSearch = ", indexSearch);
	if (_path != null)
	{
		return _path;
	}
	else
		console.log("path can't be found !");
}


function setToPathMode()
{
	mode = pathKey.letter;
	currentMode = "Pathfinder";
}

function setToEraseMode()
{
	mode = brushKey.letter;
	currentMode = "EraseMod";
}

function setToWallMode()
{
	mode = wallKey.letter;
	currentMode = "WallMod";
}

let p_percentObstacles;
let i_obstacles;
let p_gridSize;
let i_gridSize;
let i_activateGrid;
let p_currentMode;
function setupAllInformations()
{
	// two main elements.
	let mainDiv = Dom.createDiv("row interactiveBlock", document.getElementById("pageContainer"));
	let div = Dom.createDiv("col-md-3", mainDiv);


	// ensemble des bouttons permettant de switcher de mode
	
	Dom.createPara("aStarText", "Enter PathFinding Mode (defaut mod) : ", div);
	let b_pathMode = Dom.createButton("btn btn-primary btn-danger", "PathFinding Mod", div);
	b_pathMode.onclick = setToPathMode;
	Dom.createPara("","",div);

	Dom.createPara("aStarText", "Allow you to erase walls with left mouse click : ", div);
	b_eraseMode = Dom.createButton("btn btn-primary btn-danger", "EraseMod", div);
	b_eraseMode.onclick = setToEraseMode;
	Dom.createPara("","",div);

	Dom.createPara("aStarText", "Allow you to build walls with left mouse click : ", div);
	b_wallMode = Dom.createButton("btn btn-primary btn-danger", "WallMod", div);
	b_wallMode.onclick = setToWallMode;
	Dom.createPara("","",div);

	let tmpP = Dom.createPara("aStarText", "Generate new grid to see change below : ", div);
	// Elements qui concernent la taille de la grille.
	p_gridSize = Dom.createPara("aStarText", "(please enter number between 2 and 528)", div);
	i_gridSize = Dom.createInput("text", "", div);
	p_gridSize = Dom.createPara("aStarText", "Current Grid Size : " + amount, div);
	//i_gridSize.value = tmpAmount;

	// Elements qui concerne le nombre d'obstacle.
	p_percentObstacles = Dom.createPara("aStarText", "% of obstacles : " + tmpPercentObstacles, div);
	i_obstacles = Dom.createRange(0, 49, div, "");
	i_obstacles.value = percentObstacles;
	
	
	// Elements qui concerne le bouton de génération de nouvelle grille :
	Dom.createPara("","",div); // elements vide permettant le retour à la ligne
	b_generateNewGrid = Dom.createButton("btn btn-primary btn-info", "Generate new grid", div);
	b_generateNewGrid.onclick = launchNewGridWithClick;

	// elements qui concerne l'activation ou non de la grille.'
	let p_activateGrid = Dom.createPara("aStarText", "Activate Grid ? : ", div);
	i_activateGrid = Dom.createCheckBox("", div, true);

	Dom.createPara("aStarText", "ShortCut : ", div);
	Dom.createPara("aStarText", "press 'p' to enter PathFindingMod", div);
	Dom.createPara("aStarText", "press 'e' to enter EraseMod", div);
	Dom.createPara("aStarText", "press 'w' to enter WallMod", div);
	p_currentMode = Dom.createPara("aStarText", "CURRENT MODE IS : " + currentMode, div);
}


function launchNewGridWithClick()
{
	let value = parseInt(i_gridSize.value);
	if (player.pos.y > value || player.pos.x > value)
	{
		player.pos.y = floor( map(player.pos.y, 0, amount, 0, value) );
		player.pos.x = floor( map(player.pos.x, 0, amount, 0, value) );
	}
	if (i_gridSize.value != "" && i_gridSize.value > 1)
	{
		tmpAmount = value;
		p_gridSize.innerHTML = "Current Grid Size : " + value;
	}
	generateNewGrid();
}


// fonctions update GUI et grille
function UpdatePlayerPos()
{
	if (path == null || trail == null)
		return;
	if (player.pathIndex == path.length && path != null)
	{
		path = null;
		player.pathIndex = 0;
		//clearTrail();
		reverse(trail);
		pathIsDone = true;
		return;
	}
	if (player.cycle > 0)
	{
		player.cycle--;
		return;
	}
//	grid.array[player.pos.y][player.pos.x].value = 0;
	trail.push(grid.array[player.pos.y][player.pos.x]);
	player.pos.y = path[player.pathIndex].pos.y;
	player.pos.x = path[player.pathIndex].pos.x;
	grid.array[player.pos.y][player.pos.x].value = player.value;
	player.pathIndex += 1;
	player.cycle = player.cycleMax;
}

function updateAllInfo()
{
	if (tmpPercentObstacles != i_obstacles.value)
	{
		tmpPercentObstacles = parseInt(i_obstacles.value);
		p_percentObstacles.innerHTML = "% of obstacles : " + tmpPercentObstacles;
	}
	if (currentMode != tmpCurrentMode)
	{
		tmpCurrentMode = currentMode;
		p_currentMode.innerHTML = "CURRENT MODE IS : " + tmpCurrentMode;
	}
}

// ensemble de fonctions concernant le trail

function clearTrail()
{
	for(let i = 0; i < trail.length; ++i)
		grid.array[trail[i].pos.y][trail[i].pos.x].value = 0;
	trail = null;
}

function shortTrail()
{
	if (trail == null)
	{
		return;
	}
	if (cycleTrail > 0)
	{
		cycleTrail--;
		return;
	}
	grid.array[ trail[trail.length - 1].pos.y ][ trail[trail.length - 1].pos.x].value = 0;
	trail.pop();
	cycleTrail = cycleTrailMax;
	if (trail.length == 0)
	{
		trail = null;
		pathIsDone = false;
		grid.array[ player.pos.y ][ player.pos.x].value = player.value;
	}
}


function lookForPath(mousePosX, mousePosY)
{
	if (grid.array[mousePosY][mousePosX].value == 0)
	{
		if (trail != null && trail.length != 0)
		{
			pathIsDone = false;
			clearTrail();
		}
		path = null;
		player.pathIndex = 0;
		player.cycle = player.cycleMax;
		dest = new pos(mousePosY, mousePosX);
		//path = aStar(grid, player.pos, dest);
		path = idAstar(grid, player.pos, dest);
		if (path != null)
			trail = new Array();
	}
}

// fonctions utilitaires concernant  la gestion des murs
function buildNewWall(mousePosX, mousePosY)
{
	if (grid.array[mousePosY][mousePosX].value == 0)
			grid.array[mousePosY][mousePosX].value = 1;
}

function destroyWall(mousePosX, mousePosY)
{	
	if (grid.array[mousePosY][mousePosX].value == 1)
		grid.array[mousePosY][mousePosX].value = 0;
}

// fonctions d'interactions utilisateurs avec le programme

function mousePressed()
{
	let mousePosX = floor( map(mouseX, 0, size.width,  0, grid.x) );
	let mousePosY = floor( map(mouseY, 0, size.height, 0, grid.y));
	if (mousePosX < 0 || mousePosX >= grid.x || mousePosY < 0 || mousePosY >= grid.y)
		return;
	if (grid.array[mousePosY][mousePosX].value == 1)
	{
		grid.array[mousePosY][mousePosX].value = 0;
		return;
	}
	if (mode == brushKey.letter)
		destroyWall(mousePosX, mousePosY);
	else if (mode == wallKey.letter)
		buildNewWall(mousePosX, mousePosY);
	else if (mode == pathKey.letter)
		lookForPath(mousePosX, mousePosY);

}

function mouseDragged()
{
	let mousePosX = floor( map(mouseX, 0, size.width, 0, grid.x) );
	let mousePosY = floor( map(mouseY, 0, size.height, 0, grid.y));
	if (mousePosX < 0 || mousePosX >= grid.x || mousePosY < 0 || mousePosY >= grid.y)
		return;
	if (mode == wallKey.letter && grid.array[mousePosY][mousePosX].value == 0)
		grid.array[mousePosY][mousePosX].value = 1;
	else if (mode == brushKey.letter && grid.array[mousePosY][mousePosX].value == 1)
		grid.array[mousePosY][mousePosX].value = 0;
}


function keyPressed()
{
	if (keyCode == brushKey.keyCode)
		setToEraseMode();
	else if (keyCode == pathKey.keyCode)
		setToPathMode();
	else if (keyCode == wallKey.keyCode)
		setToWallMode();
}



// fonctions d'affichage  de la grille
function printContentGrid()
{
	//let playerPrint = false;
    fill(0);
	strokeWeight(1);
	stroke(0);
    for(let y = 0; y < grid.y; ++y)
        for(let x = 0; x < grid.x; ++x)
		{
			if (grid.array[y][x].value == 1)
				rect(x * render.columnWidth, y * render.lineHeight, render.columnWidth, render.lineHeight);
			if (grid.array[y][x].value == player.value)
			{
				fill(255, 0, 0);
				stroke(255, 0, 0);
				rect(x * render.columnWidth, y * render.lineHeight, render.columnWidth, render.lineHeight);
				fill(0, 0, 0);
				stroke(0, 0, 0);
			}
		}
}

function printGrid()
{
	strokeWeight(1);
	stroke(0);
	for(let i = 0; i <= grid.y; ++i)
		line(0, render.lineHeight * i, render.lineWidth, render.lineHeight * i);
	for (let i = 0; i <= grid.x; ++i)
		line(render.columnWidth * i, 0, render.columnWidth * i, render.columnHeight);
}


function printPath()
{
	if (path == null || path.length == 0)
	{
		return;
	}
	strokeWeight(2);
	stroke(127,255,0);
	let offsetX = render.columnWidth / 2;
	let offsetY = render.lineHeight / 2;
	for(let i = 1; i < path.length; ++i)
	{
		if (path[i].value != player.value)
			line(path[i - 1].pos.x * render.columnWidth + offsetX, path[i - 1].pos.y * render.lineHeight + offsetY, path[i].pos.x * render.columnWidth + offsetX, path[i].pos.y * render.lineHeight + offsetY);
	}
}

// Fonctions de base de la librairie p5js
function setup() 
{
	frameRate(60);
	setupAllInformations();
	generateNewGrid();
}

function draw()
{
	background(240);
	updateAllInfo();
	if (i_activateGrid.checked)
		printGrid();
	printContentGrid();
	UpdatePlayerPos();
	printPath();
	if (pathIsDone == true)
		shortTrail();
}
