//
//  DishModel.swift
//  DatabaseTutorial
//
//  Created by Dana on 12.11.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import Foundation
class DishModel: NSObject{
    //properties
    var name: String?
    var portion: Double?
    var price: Int?
    var descriptionOfDish: String?
    var dishID: String?
    
    //empty constructor
    
    override init()
    {
        
    }
    
    //construct with @name, @address, @latitude, and @longitude parameters
    
    init(name: String, portion: Double, price: Int, descriptionOfDish: String, dishID: String) {
        
        self.name = name
        self.portion = portion
        self.price = price
        self.descriptionOfDish = descriptionOfDish
        self.dishID = dishID
        
    }
    
    //prints object's current state
    
    override var description: String {
        return "Name: \(name), Portion: \(portion), Price: \(price), Description: \(descriptionOfDish), DishID: \(dishID)"
        
    }
    
}
