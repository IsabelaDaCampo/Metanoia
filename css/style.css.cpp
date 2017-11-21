*{
	margin: 0;
	padding: 0;
}

body{
	text-align: center;
	background-color: #555;
}

#game{
	position: relative;
	width: 1325px;
	height: 495px;
	border: 1px solid #111;
	border-radius: 10px;
	margin: 10px auto;
	background-color: #563D00;
}

.card{
	width: 160px;
	height: 240px;
	perspective: 600px;
	position: absolute;
	border-radius: 10px;
}

.face{
	border-radius: 10px;
	width: 100%;
	height: 100%;
	position: absolute;
	transition: all 1s;
	backface-visibility: hidden;
}

.front{
	transform: rotateY(-180deg);
}

.flipped.front{
	transform: rotateY(0deg);
}

.back{
	background: url(../img/verso.jpg);
}

.flipped.back{
	transform: rotateY(180deg);
}

.card:hover, .face.flipped{
	box-shadow: 0 0 10px #aaa;
}

.face.flipped.match{
	box-shadow: 0 0 10px #0f0;
}

#match{
	position: relative;
	margin: 0 auto;
	top: 250px;
	z-index: -1;
	opacity: 1;
	transition-property: top, opacity;
	transition-duration: 1.5s;
}

#gameOver{
	position: absolute;
	top: 0;
	border-radius: 5px;
	width: 100%;
	height: 100%;
	background-color: rgba(0,0,0,0.5);
	z-index: -2;
}

#imgGameOver{
	margin-top: 100px;
}
