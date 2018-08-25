//
//  HomeModel.swift
//  DatabaseTutorial
//
//  Created by Dana on 12.11.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import Foundation

protocol HomeModelProtocol: class{
    func itemsDownloaded(items: NSArray)
}

class HomeModel: NSObject, URLSessionDataDelegate {
    
    //properties
    
    weak var delegate: HomeModelProtocol!
    
    var data = Data()
    
    let urlPath: String = "http://localhost/index.php"
    //this will be changed to the path where service.php lives

    func downloadItems() {
        
        let url: URL = URL(string: urlPath)!
        let defaultSession = Foundation.URLSession(configuration: URLSessionConfiguration.default)
        
        let task = defaultSession.dataTask(with: url) { (data, response, error) in
            
            if error != nil {
                print("Failed to download data")
            }else {
                print("Data downloaded")
                self.parseJSON(data!)
            }
            
        }
        
        task.resume()
    }
    
    func parseJSON(_ data:Data) {
        
        var jsonResult = NSArray()
        
        do{
            jsonResult = try JSONSerialization.jsonObject(with: data, options:JSONSerialization.ReadingOptions.allowFragments) as! NSArray
            
        } catch let error as NSError {
            print(error)
            
        }
        
        var jsonElement = NSDictionary()
        let dishes = NSMutableArray()
        
        for i in 0 ..< jsonResult.count
        {
            
            jsonElement = jsonResult[i] as! NSDictionary
            
            let dish = DishModel()
                        
            //the following insures none of the JsonElement values are nil through optional binding
            if let name = jsonElement["Name"] as? String,
                let portion = jsonElement["Portion"] as? Double,
                let price = jsonElement["Price"] as? Int,
                let descriptionOfDish = jsonElement["Description"] as? String,
                let dishID = jsonElement["dishID"] as? String
            {
                dish.name = name
                dish.portion = portion
                dish.price = price
                dish.descriptionOfDish = descriptionOfDish
                dish.dishID = dishID
            }
            
            dishes.add(dish)
            
        }
        
        DispatchQueue.main.async(execute: { () -> Void in
            
            self.delegate.itemsDownloaded(items: dishes)
            
        })
    }
}
