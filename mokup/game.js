// Configuración inicial
const canvas = document.createElement("canvas");
canvas.width = 400;
canvas.height = 400;
document.body.appendChild(canvas);
const ctx = canvas.getContext("2d");

// Tamaño de la cuadrícula
const gridSize = 40;

// Jugadores y bloque
const player1 = { x: 4, y: 3, color: "blue" }; // Jugador en la mitad superior
const player2 = { x: 4, y: 6, color: "green" }; // Jugador en la mitad inferior
const block = { x: 4, y: 8, color: "gray" };

// Límites
const walls = {
  top: 0,
  bottom: canvas.height / gridSize - 1,
  left: 0,
  right: canvas.width / gridSize - 1,
};

// Dibujar cuadrícula
function drawGrid() {
  ctx.strokeStyle = "#ccc";
  for (let x = 0; x <= canvas.width; x += gridSize) {
    ctx.beginPath();
    ctx.moveTo(x, 0);
    ctx.lineTo(x, canvas.height);
    ctx.stroke();
  }
  for (let y = 0; y <= canvas.height; y += gridSize) {
    ctx.beginPath();
    ctx.moveTo(0, y);
    ctx.lineTo(canvas.width, y);
    ctx.stroke();
  }
}

// Dibujar jugador o bloque
function drawEntity(entity) {
  ctx.fillStyle = entity.color;
  ctx.fillRect(
    entity.x * gridSize + 1,
    entity.y * gridSize + 1,
    gridSize - 2,
    gridSize - 2
  );
}

// Dibujar muro divisor
function drawWalls() {
  ctx.strokeStyle = "black";
  ctx.beginPath();
  ctx.moveTo(0, canvas.height / 2);
  ctx.lineTo(canvas.width, canvas.height / 2);
  ctx.stroke();
}

// Actualizar y dibujar
function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  drawGrid();
  drawWalls();
  drawEntity(player1);
  drawEntity(player2);
  drawEntity(block);
}

draw();

// Movimiento de los jugadores
function movePlayer(player, dx, dy) {
  const newX = player.x + dx;
  const newY = player.y + dy;

  // Restricciones por pared
  if (
    newX < walls.left ||
    newX > walls.right ||
    newY < walls.top ||
    newY > walls.bottom
  ) {
    return;
  }

  // Restricciones por la línea divisoria
  if (player === player1 && newY >= canvas.height / gridSize / 2 - 1) {
    return;
  }
  if (player === player2 && newY <= canvas.height / gridSize / 2) {
    return;
  }

  // Si es el jugador 2, verificar interacción con el bloque
  if (player === player2 && newX === block.x && newY === block.y) {
    const blockNewX = block.x + dx;
    const blockNewY = block.y + dy;

    // Verificar si el bloque puede moverse
    if (
      blockNewX >= walls.left &&
      blockNewX <= walls.right &&
      blockNewY >= canvas.height / gridSize / 2 &&
      blockNewY <= walls.bottom
    ) {
      block.x = blockNewX;
      block.y = blockNewY;
    } else {
      return; // Bloque no puede moverse, jugador tampoco
    }
  }

  player.x = newX;
  player.y = newY;
}

// Escuchar eventos de teclado
window.addEventListener("keydown", (e) => {
  switch (e.key) {
    case "ArrowUp":
      movePlayer(player1, 0, -1);
      break;
    case "ArrowDown":
      movePlayer(player1, 0, 1);
      break;
    case "ArrowLeft":
      movePlayer(player1, -1, 0);
      break;
    case "ArrowRight":
      movePlayer(player1, 1, 0);
      break;
    case "w":
      movePlayer(player2, 0, -1);
      break;
    case "s":
      movePlayer(player2, 0, 1);
      break;
    case "a":
      movePlayer(player2, -1, 0);
      break;
    case "d":
      movePlayer(player2, 1, 0);
      break;
  }
  draw();
});
