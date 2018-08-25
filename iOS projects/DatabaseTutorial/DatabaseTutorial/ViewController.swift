//
//  ViewController.swift
//  DatabaseTutorial
//
//  Created by Dana on 12.11.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, HomeModelProtocol {

    @IBOutlet weak var listTableView: UITableView!
    
    
    var feedItems: NSArray = NSArray()
    var selectedLocation : DishModel = DishModel()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.listTableView.delegate = self
        self.listTableView.dataSource = self
        
        let homeModel = HomeModel()
        homeModel.delegate = self
        homeModel.downloadItems()
        
    }

    func itemsDownloaded(items: NSArray) {
        
        feedItems = items
        self.listTableView.reloadData()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // Return the number of feed items
        return feedItems.count
        
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        // Retrieve cell
        let cellIdentifier: String = "BasicCell"
        let myCell: UITableViewCell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier)!
        // Get the location to be shown
        let item: DishModel = feedItems[indexPath.row] as! DishModel
        // Get references to labels of cell
        myCell.textLabel!.text = item.name
        
        return myCell
    }
    
    
    
    

}

