package e8;

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

class TreeNode {
	private String label;
	private String elabel;
	private ArrayList<TreeNode> children;

	TreeNode(String s) {
		label = s;
		children = new ArrayList<>();
	}

	void setLabel(String s) {
		label = s;
	}

	void setElabel(String s) {
		elabel = s;
	}

	String getLabel() {
		return label;
	}

	String getElabel() {
		return elabel;
	}

	int getChildrenNum() {
		return children.size();
	}

	TreeNode getChild(int i) {
		if (0 <= i && i < children.size())
			return children.get(i);
		else
			return null;
	}

	void addChild(TreeNode n) {
		children.add(n);
	}
}

class DataList {
	private LinkedList<ArrayList<String>> dataList;

	DataList() {
		dataList = new LinkedList<>();
	}

	void add(String line) {
		String[] token = line.split("\\s+");
		ArrayList<String> lineData = new ArrayList<>(Arrays.asList(token));
		add(lineData);
	}

	void add(ArrayList<String> d) {
		dataList.add(d);
	}

	ArrayList<String> get(int i) {
		return dataList.get(i);
	}

	int size() {
		return dataList.size();
	}
}

class AttrList {
	private ArrayList<String> attrList;

	AttrList() {
		attrList = new ArrayList<>();
	}

	void setAttributes(String s) {
		String[] token = s.split("\\s");
		for (int i = 0; i < token.length; i++)
			add(token[i]);
	}

	void add(String s) {
		attrList.add(s);
	}

	String get(int i) {
		return attrList.get(i);
	}

	int size() {
		return attrList.size();
	}

	int indexOf(String s) {
		return attrList.indexOf(s);
	}
}

public class SimpleDT {
	private String fileName;
	private AttrList attrList;
	private DataList dataList;
	private TreeNode rootNode;

	SimpleDT(String s) {
		fileName = s;
		attrList = new AttrList();
		dataList = new DataList();
	}
	
	// ファイルを読み込んでデータを設定する。
	void readFile() {
		try {
			BufferedReader in = new BufferedReader(new FileReader(fileName));
			String line = in.readLine();
			attrList.setAttributes(line);
			while ((line = in.readLine()) != null) {
				dataList.add(line);
			}
			in.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.printf("read %d records\n", dataList.size());
	}
	
	// データを指定された列、指定された数で分割する。
	DataList[] divideData(DataList dlist, int col, int numOfDivisions) {
		DataList[] dividedDataLists = new DataList[numOfDivisions];
		for (int i = 0; i < numOfDivisions; i++)
			dividedDataLists[i] = new DataList();
		HashMap<String, Integer> attrValueIndexMap = new HashMap<>();
		int index;

		for (int i = 0; i < dlist.size(); i++) {
			ArrayList<String> data = dlist.get(i);
			String value = data.get(col);
			if (attrValueIndexMap.containsKey(value))
				index = attrValueIndexMap.get(value);
			else {
				index = attrValueIndexMap.size();
				attrValueIndexMap.put(value, index);
			}
			dividedDataLists[index].add(data);
		}
		return dividedDataLists;
	}
	
	// 指定された列を除外した新しい属性リストを返す
	AttrList deleteAttribute(AttrList orgAttrList, int col) {
		AttrList newAttrList = new AttrList();
		for (int i = 0; i < orgAttrList.size(); i++) {
			if (i == col)
				continue;
			newAttrList.add(orgAttrList.get(i));
		}
		return newAttrList;
	}
	
	//　底2の対数を計算する
	double log2(double d) {
		return Math.log(d) / Math.log(2);
	}
	
	// 指定された列と属性値に対する情報量を計算する
	double subInfo(DataList dlist, int col, String attrValue) {
		double info = 0.0;
		int total = 0;
		
		// "play"　と "not play"を格納する変数
		int playCount = 0;
		int notPlayCount = 0;
		
		// クラスごとの頻度を計算
		for(int i = 0; i < dlist.size(); i++) {
			ArrayList<String> data = dlist.get(i);
			
			if(data.get(col).equals(attrValue)) {
				total++;
				String classLabel = data.get(data.size() - 1);
				if(classLabel.equals("play")) {
					playCount++;
				}else if(classLabel.equals("not_play")){
					notPlayCount++;
				}
			}
		}
		
		// サブ情報量を計算する
		if(playCount > 0) {
			double playProbability = (double)playCount / total;
			info -= playProbability * log2(playProbability);
		}
		
		if(notPlayCount > 0) {
			double notPlayProbability = (double)notPlayCount / total;
			info -= notPlayProbability * log2(notPlayProbability);
		}
		
		return info;
	}
	
	// 指定された列と属性値に対する条件付き情報量を計算する
	double postInfo(DataList dlist, int col, HashMap<String, Integer> attrValueFreqMap) {
		double info = 0.0;
		
		// 各属性値に対する条件付き情報量を計算
		for(Entry<String, Integer> entry : attrValueFreqMap.entrySet()) {
			String attrValue = entry.getKey();
			int freq = entry.getValue();
			double probability = (double)freq / dlist.size();
			double subInfo = subInfo(dlist, col, attrValue);
			info += probability * subInfo;
		}
		
		return info;
	}
	
	// 事前情報量を計算する
	double preInfo(int numOfData, HashMap<String, Integer> cDist) {
		double info = 0.0;
		
		// 事前情報量を計算
		for(int freq : cDist.values()) {
			double probability = (double)freq / numOfData;
			info -= probability * log2(probability);
		}
		
		return info;
	}

	// 与えられた属性値の頻度マップから最頻値を見つける
	String findMajority(HashMap<String, Integer> attrValueFreqMap) {
		int maxFreq = 0;
		String maxKey = null;
		for (String key : attrValueFreqMap.keySet()) {
			if (maxFreq < attrValueFreqMap.get(key)) {
				maxFreq = attrValueFreqMap.get(key);
				maxKey = key;
			}
		}
		return maxKey;
	}
	
	// 各属性の属性値ごとの頻度マップのリストを取得する
	ArrayList<HashMap<String, Integer>> getAttrValueFreqMapList(DataList dlist, AttrList alist) {
		ArrayList<HashMap<String, Integer>> attrValueFreqMap = new ArrayList<>();
		
		// 各属性に対して頻度マップを計算
		for(int i = 0; i < alist.size(); i++) {
			HashMap<String, Integer> attrValueFreqMap2 = new HashMap<>();
			int col = attrList.indexOf(alist.get(i));
			
			//属性値ごとの出現回数を計算
			for(int j = 0; j < dlist.size(); j++) {
				ArrayList<String> data = dlist.get(j);
				String attrValue = data.get(col);
				attrValueFreqMap2.put(attrValue, attrValueFreqMap2.getOrDefault(attrValue, 0) + 1);
			}
			
			// 属性ごとの頻度マップをリストに追加
			attrValueFreqMap.add(attrValueFreqMap2);
		}
		
		return attrValueFreqMap;
	}

	// 決定木のルートノードを作成する
	TreeNode makeTree(DataList dlist, AttrList alist) {
		ArrayList<HashMap<String, Integer>> attrValueFreqMapList = getAttrValueFreqMapList(dlist, alist);
		DataList[] dividedDataLists;
		AttrList newAttrList;
		String clsName = null;
		double maxGain = 0.0;
		int maxId = -1;
		int col;
		
		// 属性が一つしかない場合
		if (alist.size() == 1) {
			clsName = findMajority(attrValueFreqMapList.get(0));
			return new TreeNode(clsName);
		}

		// クラスが一つしかない場合
		if (attrValueFreqMapList.get(alist.size() - 1).size() == 1) {
			for (String key : attrValueFreqMapList.get(alist.size() - 1).keySet())
				clsName = key;
			return new TreeNode(clsName);
		}

		// 事前情報量を計算
		double preInfo = preInfo(dlist.size(), attrValueFreqMapList.get(alist.size() - 1));
		System.out.printf("  preInfo: %.3f\n", preInfo);

		// 各属性に対して情報利得を計算
		for (int i = 0; i < alist.size() - 1; i++) {
			double postInfo = postInfo(dlist, attrList.indexOf(alist.get(i)), attrValueFreqMapList.get(i));
			double gain = preInfo - postInfo;
			System.out.printf("    gain for %s: %.3f\n", alist.get(i), gain);
			if (maxGain < gain) {
				maxGain = gain;
				maxId = i;
			}
		}
		
		// 情報利得が0の場合は最頻値でクラスを割り当てる
		if (maxGain == 0.0) {
			clsName = findMajority(attrValueFreqMapList.get(alist.size() - 1));
			return new TreeNode(clsName);
		}

		// 最大情報利得をもつ属性の列を取得
		col = attrList.indexOf(alist.get(maxId));
		dividedDataLists = divideData(dlist, col, attrValueFreqMapList.get(maxId).size());
		newAttrList = deleteAttribute(alist, maxId);
		TreeNode newNode = new TreeNode(alist.get(maxId));

		// 各分割データに対して再帰的にツリーを作成
		for (int i = 0; i < dividedDataLists.length; i++) {
			if (dividedDataLists[i].size() != 0) {
				TreeNode tmp = makeTree(dividedDataLists[i], newAttrList);
				tmp.setElabel(dividedDataLists[i].get(0).get(col));
				newNode.addChild(tmp);
			}
		}
		return newNode;
	}
	
	// 決定木を構築するメソッド
	void buildTree() {
		rootNode = makeTree(dataList, attrList);
	}
	
	// ノードを表示するメソッド
	void printNode(TreeNode node, int level) {
	    String indent1 = "\n";
	    String indent2 = "|   ".repeat(level * 1);	    
	    
	    // ノードが葉ノードかどうかを判定する
	    if (node.getChildrenNum() == 0) {
	        // 葉ノードの場合は、そのラベルを出力する
	    	System.out.printf(": " + node.getLabel() + indent1);
	    } else {
	    	if(level != 0) {
	    		System.out.printf(indent1);
	    	}
	        // 葉ノードでない場合は、そのノードのすべての子ノードを取得する
	        for (int i = 0; i < node.getChildrenNum(); i++) {
	            TreeNode child = node.getChild(i);
	            // それぞれの子ノードについて、その属性値とその子ノードを出力する
	            System.out.printf(indent2 + node.getLabel() + " = " +  child.getElabel());
	           
	            // 子ノードに対して、再帰的にprintNodeメソッドを呼び出す
	            printNode(child, level + 1);
	        }
	    }
	}
	
	// 決定木全体を表示するメソッド
	void printTree() {
		printNode(rootNode, 0);
	}

	public void testGetAttrValueFreqMapList() {
		ArrayList<HashMap<String, Integer>> attrValueFreqMapList = getAttrValueFreqMapList(dataList, attrList);
		for (int i = 0; i < attrValueFreqMapList.size(); i++) {
			String attrName = attrList.get(i);
			HashMap<String, Integer> attrValueFreqMap = attrValueFreqMapList.get(i);
			for (Entry<String, Integer> attrValueFreqEntry : attrValueFreqMap.entrySet()) {
				String attrValue = attrValueFreqEntry.getKey();
				int freq = attrValueFreqEntry.getValue();
				System.out.printf("%s %s %d\n", attrName, attrValue, freq);
			}
		}
	}

	public void testPreInfo() {
		ArrayList<HashMap<String, Integer>> attrValueFreqMapList = getAttrValueFreqMapList(dataList, attrList);
		double preInfo = preInfo(dataList.size(), attrValueFreqMapList.get(attrList.size() - 1));
		System.out.printf("Root preInfo %.3f\n", preInfo);
	}

	public void testSubInfo() {
		ArrayList<HashMap<String, Integer>> attrValueFreqMapList = getAttrValueFreqMapList(dataList, attrList);
		HashMap<String, Integer> attrValueFreqMap = attrValueFreqMapList.get(0);
		for (String attrValue : attrValueFreqMap.keySet()) {
			double subInfo = subInfo(dataList, 0, attrValue);
			System.out.printf("%s %s subInfo %.3f\n", attrList.get(0), attrValue, subInfo);
		}
	}

	public void testPostInfo() {
		ArrayList<HashMap<String, Integer>> attrValueFreqMapList = getAttrValueFreqMapList(dataList, attrList);
		for (int i = 0; i < attrValueFreqMapList.size() - 1; i++) {
			double postInfo = postInfo(dataList, i, attrValueFreqMapList.get(i));
			System.out.printf("%s postInfo %.3f\n", attrList.get(i), postInfo);
		}
	}

	public static void main(String[] args) {
		if (args.length != 2) {
			System.err.println(
					"java p8.SimpleDT [testGetAttrValueFreqMapList|testPreInfo|testSubInfo|testPostInfo|testPrintTree] [input file path]");
			System.exit(-1);
		}
		String testType = args[0];
		String inputFilePath = args[1];
		SimpleDT dt = new SimpleDT(inputFilePath);
		dt.readFile();

		switch (testType) {
		case "testGetAttrValueFreqMapList":
			dt.testGetAttrValueFreqMapList();
			break;
		case "testPreInfo":
			dt.testPreInfo();
			break;
		case "testSubInfo":
			dt.testSubInfo();
			break;
		case "testPostInfo":
			dt.testPostInfo();
			break;
		case "testPrintTree":
			dt.buildTree();
			dt.printTree();
			break;
		}

	}

}
