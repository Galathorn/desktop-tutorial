// définition des variables environnementales

let env = {};
env.width = 900;
env.height = 900;
env.squareSize = 3;

let color; // couleurs des carrés du npuzzle
let npuzzle; // le npuzzle proprement dit
let path = null; // variable stockant l'ensemble des mouvement à faire pour arriver au résultat final.'

let canvas; 
let render;

let pathIndex = 0;

let animationAreOn = true;
let animator = null;
let scrambler = null;

let PERCENT = 20;
let tmpPercent = PERCENT;
let CYCLE_MAX = 0;
let AMOUNT_MOVES = 14;

let amountStack = 7500;
let stackNpuzzle;

function setupStack()
{
	stackNpuzzle = new Array();
	for(let y = 0; y < amountStack; ++y)
		stackNpuzzle.push(npuzzle.copy());
}

function mousePressed()
{
	if (animator != null || npuzzle == null)
		return;
	let mousePosX = floor(map(mouseX, 0, env.width, 0, env.squareSize));
	let mousePosY = floor(map(mouseY, 0, env.height, 0, env.squareSize));
	npuzzle.applyMove(mousePosY, mousePosX);
}

function getRandomInt(max)
{
  return Math.floor(Math.random() * Math.floor(max));
}

// cette fonction est appelé lorsque le bouton launch A* est cliqué.
function launchAstar()
{
	pathIndex = 0;
	npuzzle.gCost = 0;
	npuzzle.parent = 0;
	npuzzle.id = 0;
	npuzzle.defMove = null;
	path = aStar(npuzzle.copy());
	console.log("stack size after path : ", stackNpuzzle.length);
}

function launchScramble()
{
	path = null;
	scrambler.isOn = true;
}

function setup() 
{
	frameRate(80);
	setupColor(0, 0, 0);
	setupRender();
	generateNewEnvironment();
	setupNpuzzle();
	setupScrambler();
	setupDom();
	setupStack();
	console.log("Setup is ready");
	console.log("stack size : ", stackNpuzzle.length);
}

function checkAnimation()
{
	if (animator != null)
		if (animator.animate() == false)
		{
			npuzzle.swapNode(npuzzle.grid, animator.originStartNodePos.y, animator.originStartNodePos.x, animator.originEndNodePos.y, animator.originEndNodePos.x);
		//	console.log("Animation end");
	//		console.log(npuzzle.hCost());
			animator = null;
		}
}

function checkNextScramble()
{
//	scrambler.isOn = false;
//	return;
	if (scrambler == null || scrambler.isOn == false || animator != null)
		return;
	scrambler.oneRandomMove();
}

function checkNextMove()
{
	if (path == null || animator != null || scrambler.isOn == true)
		return;
	if (path[pathIndex] == "UP")
	{
		console.log("UP : ", path[pathIndex]);
		if (npuzzle.Up() == true)
			pathIndex++;
	}
	else if (path[pathIndex] == "DOWN")
	{
		console.log("DOWN : ", path[pathIndex]);
		if (npuzzle.Down() == true)
			pathIndex++;
	}
	else if (path[pathIndex] == "RIGHT")
	{
		console.log("RIGHT : ", path[pathIndex]);

		if (npuzzle.Right() == true)
			pathIndex++;
	}
	else if (path[pathIndex] == "LEFT")
	{
		console.log("LEFT : ", path[pathIndex]);
		if (npuzzle.Left() == true)
			pathIndex++;
	}
}

function checkForAnimationSpeed()
{
	if (i_obstacles.value != tmpPercent)
	{
		PERCENT = parseInt(i_obstacles.value);
		tmpPercent = PERCENT;
		p_percentAnim.innerHTML = "Animation Speed : " + tmpPercent;
	}
}

function updateInformation()
{
	checkForAnimationSpeed();
	checkNextScramble();
	checkAnimation();
	checkNextMove();
}

function draw()
{
	if (npuzzle == null)
		return;
	background(240);
	updateInformation();
	npuzzle.print(color);

}
