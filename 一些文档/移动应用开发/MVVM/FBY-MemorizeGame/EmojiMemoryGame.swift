//
//  EmojiMemoryGame.swift
//  FBY-MemorizeGame
//
//  Created by 付宝莹 on 2024/10/12.
//

import SwiftUI



class EmojiMemoryGame: ObservableObject {
    private static let emojis = ["👻","🎃","🕷️","😈","💀","🕸️","🧑‍🌾","🐱","👹","😱","☠️","🍭"]
    
    private static func createMemoryGame() -> MemoryGame<String> {
        return MemoryGame(numberOfPairsOfCards:10){pairIndex in
            if emojis.indices.contains(pairIndex){
                return emojis[pairIndex]
            }else{
                return "⚠️error"
            }
        }
    }
    
    
    
    @Published private var game = createMemoryGame()
    
    var cards: Array<MemoryGame<String>.Card>{
        return game.cards
    }
    
    //MAEK: - Intents
    
    func shuffle(){
        game.shuffle()
        objectWillChange.send()
    }
    func choose(_ card: MemoryGame<String>.Card){
        game.choose(card)
    }
}
