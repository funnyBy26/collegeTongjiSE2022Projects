//
//  MemorizeGame.swift
//  FBY-MemorizeGame
//
//  Created by 付宝莹 on 2024/10/12.
//

import Foundation

struct MemoryGame<CardContent>{
    private(set) var cards: Array<Card>
    
    init(numberOfPairsOfCards: Int, cardContentFactory: (Int) -> CardContent){
        cards = Array<Card>()
        // add numberOfPairsOfCards * 2 cards
        for pairIndex in 0..<max(2,numberOfPairsOfCards){
            let content: CardContent = cardContentFactory(pairIndex)
            cards.append(Card(content: content ))
            cards.append(Card(content: content))
        }
        
    }
    
    func choose(_ card: Card){
        
    }
    
    mutating func shuffle(){
        cards.shuffle()
        print(cards)
    }
    
    struct Card{
        var isFaceUp = true
        var isMatched = false
        let content: CardContent
    }
    
}
