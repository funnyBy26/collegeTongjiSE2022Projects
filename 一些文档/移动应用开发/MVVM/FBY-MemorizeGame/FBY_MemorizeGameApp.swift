//
//  FBY_MemorizeGameApp.swift
//  FBY-MemorizeGame
//
//  Created by 付宝莹 on 2024/10/12.
//

import SwiftUI

@main
struct FBY_MemorizeGameApp: App {
    @StateObject var game = EmojiMemoryGame()
    
    var body: some Scene {
        WindowGroup {
            EmojiMemoryGameView(EmojiViewModel: game)
        }
    }
}
