(function(){
	//array que armazenar� os objetos com src e id de 1 a 8
	var images = [];
	
	//imagem a ser exibida em caso de acerto
	var matchSign = document.querySelector("#match");
	
	//imagem de fim do jogo
	var modal = document.querySelector("#gameOver");
	
	//array que armazena as cartas viradas
	var flippedCards = [];
	
	//vari�vel contadora de acertos. ao chegar em 8 o jogo termina
	var matches = 0;
	
	//estrutura de atribiu��o das imagens aos card
	for(var i = 0; i < 17; i++){
		//cria um objeto img com um src e um id
		var img = {
			src: "img/" + i + ".jpg",
			id: i%8
		};
		
		//inserer o objeto criado no array
		images.push(img);
	}
	
	//chama a fun��o de inicializa��o do jogo
	startGame();
	
	//fun��o de inicializa��o do jogo
	function startGame(){
		//zera o array de cartas viradas
		flippedCards = [];
		
		//zera o contador de acertos
		matches = 0;
		
		//embaralhamento do array de imagens
		images = randomSort(images);
		
		//lista de elementos div com as classes back e front
		var backFaces = document.getElementsByClassName("back");
		var frontFaces = document.getElementsByClassName("front");
		
		//posicionamento das cartas e adi��o do evento click
		for(var i = 0; i < 17; i++){
			//limpa as cartas marcadas
			backFaces[i].classList.remove("match","flipped");
			frontFaces[i].classList.remove("match","flipped");
			
			//posiciona as cartas no tabuleiro
			var card = document.querySelector("#card" + i);
			card.style.left = (i % 8) === 0 ? 5 + "px" : 5 + ((i % 8) * 165) + "px";
			card.style.top = i/8 >= 1 ? 250 + "px" : 5 + "px";
			
			//adiciona �s cartas o evento click chamando a fun��o que vira as cartas
			card.addEventListener("click",flipCard,false);
			
			//adiciona as imagens �s cartas
			frontFaces[i].style.background = "url('" + images[i].src + "')";
			frontFaces[i].setAttribute("id",images[i].id);
		}
		
		//joga a imagem de game over para o plano de fundo
		modal.style.zIndex = "-2";
		
		//remove o evento click da imagem de game over
		modal.removeEventListener('click',function(){
			startGame();
		},false);
	}//fim da fun��o de inicializa��o do jogo
	
	
	//fun��o que vira as cartas
	function flipCard(){
		//verifica se o n�mero de cartas viradas � menor que 2
		if(flippedCards.length < 2){
			//pega as faces da carta clicada
			var faces = this.getElementsByClassName("face");
			
			//confere se a carta j� est� virada, impedindo que a mesma carta seja virada duas vezes
			if(faces[0].classList[2]){
				return;
			}
			
			//adiciona a classe fliped �s faces da carta para que sejam viradas
			faces[0].classList.toggle("flipped");
			faces[1].classList.toggle("flipped");
			
			//adiciona a carta clicada ao array de cartas viradas
			flippedCards.push(this);
			
			//verifica se o n�mero de cartas no array de cartas viradas � igual a 2
			if(flippedCards.length === 2){
				//compara o id das cartas viradas para ver se houve um acerto
				if(flippedCards[0].childNodes[3].id === flippedCards[1].childNodes[3].id){
					//em caso de acerto adiciona a classe match a todas as faces das duas cartas presentes no array de cartas viradas
					flippedCards[0].childNodes[1].classList.toggle("match");
					flippedCards[0].childNodes[3].classList.toggle("match");
					flippedCards[1].childNodes[1].classList.toggle("match");
					flippedCards[1].childNodes[3].classList.toggle("match");
					
					//chama a fun��o que exibe a mensagem MATCH
					matchCardsSign();
					
					//limpa o array de cartas viradas
					flippedCards = [];
					
					//soma um ao contador de acertos
					matches++;
					
					//verifica se o contador de acertos chegou a 8
					if(matches >= 8){
						//caso haja 8 acertos, chama a fun��o que finaliza o jogo
						gameOver();
					}
				} 
			} 
		} else {
			//em caso haver duas cartas no array de cartas viradas (terceiro click) remove a classe flipped das cartas no array de cartas viradas
			flippedCards[0].childNodes[1].classList.toggle("flipped");
			flippedCards[0].childNodes[3].classList.toggle("flipped");
			flippedCards[1].childNodes[1].classList.toggle("flipped");
			flippedCards[1].childNodes[3].classList.toggle("flipped");
			
			//limpa o array de cartas viradas
			flippedCards = [];
		}
	}
	
	
	//fun��o que embaralha as cartas recebendo um array de cartas por par�metro
	function randomSort(array){
		//cria um array vazio
		var newArray = [];
		
		//executa a estrutura enquanto o novo array n�o atingir o mesmo n�mero de elementos do arrau passado por par�metro
		while(newArray.length !== array.length){
			//cria uma vari�vel i recebendo um n�mero aleat�rio entre 0 e o n�mero de elementos no array -1
			var i = Math.floor(Math.random()*array.length);
			
			//verifica se o elemento indicado pelo �ndice i j� existe no array novo
			if(newArray.indexOf(array[i]) < 0){
				//caso n�o exista � inserido
				newArray.push(array[i]);
			}
		}
		
		//retorna o array novo, que possui os elementos do array passado por par�metro embaralhados
		return newArray;
	}//fim da fun��o que embaralha as cartas
	
	
	//fun��o que gera o sinal de MATCH
	function matchCardsSign(){
		//joga a mensagem de MATCH para o primeiro plano
		matchSign.style.zIndex = "1";
		
		//deixa a mensagem transparente
		matchSign.style.opacity = "0";
		
		//move a mensagem para cima
		matchSign.style.top = "150px";
		
		//fun��o executada ap�s 1.5 segundo
		setTimeout(function(){
			//joga a mensagem de MATCH para o plano de fundo
			matchSign.style.zIndex = "-1";
			
			//remove a transpar�ncia da mansagem
			matchSign.style.opacity = "1";
			
			//move a mensagem para o centro da tela
			matchSign.style.top = "250px";
		},1500);
	}//fim da fun��o que exibe mensagem de MATCH
	
	//fun��o de fim do jogo
	function gameOver(){
		//joga a mensagem de fim do jogo para o plano da frente
		modal.style.zIndex = "99";
		
		//adiciona o evento click � imagem de game over
		modal.addEventListener('click',function(){
			//chama a fun��o que reinicia o jogo
			startGame();
		},false);
	}
}());
