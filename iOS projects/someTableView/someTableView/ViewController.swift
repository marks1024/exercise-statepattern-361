//
//  ViewController.swift
//  someTableView
//
//  Created by Dana on 09.11.2017.
//  Copyright © 2017 Dana Zhumabekova. All rights reserved.
//

import UIKit


struct somePerson{
    var _number: String?
    var _name: String?
}

class ViewController: UIViewController,UITableViewDataSource, UITableViewDelegate {
    
    var someList = [somePerson(_number: "87345", _name: "Tony"), somePerson(_number: "56479", _name: "Kevin"), somePerson (_number: "676543", _name: "David"),somePerson(_number: "43434", _name: "Anna"), somePerson(_number: "43343434", _name: "Lee"), somePerson(_number: "43434", _name: "Ben"),somePerson(_number: "4343434", _name: "Arman")]
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return someList.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "id") as? TableViewCell
        
        cell?.someName.text = someList[indexPath.row]._name
        cell?.someNumber.text = someList[indexPath.row]._number
        
        return cell!
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        if segue.identifier == "toDetails"{
            let vc = segue.destination as? InfoViewController
            vc?.someName = someList[(someTableView.indexPathForSelectedRow?.item)!]._name
            vc?.someNumber = someList[(someTableView.indexPathForSelectedRow?.item)!]._number
            
        }
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        performSegue(withIdentifier: "toDetails", sender: self)
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 41
    }
    
    @IBOutlet weak var someTableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        someTableView.delegate = self
        someTableView.dataSource = self
    }

    

}

