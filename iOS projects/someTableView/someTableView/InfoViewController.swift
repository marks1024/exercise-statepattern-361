
//
//  InfoViewController.swift
//  someTableView
//
//  Created by Dana on 16.11.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import UIKit

class InfoViewController: UIViewController {

    var someName: String?
    var someNumber: String?
    @IBOutlet weak var name: UILabel!
    @IBOutlet weak var personInfo: UILabel!
    @IBOutlet weak var phoneNumber: UILabel!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.name.text = self.someName
        self.phoneNumber.text = self.someNumber
        
    }

}
