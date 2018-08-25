//
//  ViewController.swift
//  Table
//
//  Created by Dana on 26.10.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import UIKit

class ViewController: UIViewController,UITableViewDelegate,UITableViewDataSource{
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 10
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "id1")
        if indexPath.section%2 == 0 {
            cell?.backgroundColor = .yellow
        } else {
            cell?.backgroundColor = .blue

        }
        return cell!
    }
    
    
    @IBOutlet weak var TableView: UITableView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        TableView.rowHeight = 200
        // Do any additional setup after loading the view, typically from a nib.
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    

}

