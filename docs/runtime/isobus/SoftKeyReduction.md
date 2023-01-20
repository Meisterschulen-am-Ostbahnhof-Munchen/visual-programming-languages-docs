# SoftKey Reduction

Die ISO 11783-6 legt fest, dass landwirtschaftliche Steuergeräte in der Lage sein sollten, sich an unterschiedliche Displays anzupassen. Eine wichtige Anforderung dabei ist die Unterstützung von Softkey-Reduktion.

Softkeys sind Tasten auf einem Display, die dem Benutzer schnellen Zugriff auf häufig verwendete Funktionen ermöglichen. Die meisten Displays haben in der Regel 12 Softkeys, aber es gibt auch Displays mit weniger Softkeys, wie z.B. 6, 8 oder 10. Um sich an diese unterschiedlichen Displays anzupassen, muss das Steuergerät in der Lage sein, die Anzahl der angezeigten Softkeys zu reduzieren, um sicherzustellen, dass alle Funktionen auf dem Display angezeigt werden können.

Die Notwendigkeit der Softkey-Reduktion in der ISO 11783-6 liegt darin, dass es unterschiedliche Displays mit unterschiedlichen Anforderungen in Bezug auf die Anzahl der Softkeys gibt. Durch die Unterstützung von Softkey-Reduktion kann sichergestellt werden, dass das Steuergerät auf jedem Display ordnungsgemäß funktioniert und der Benutzer alle Funktionen bequem erreichen kann.

In einer Beispielhaften Softkeymask, mit 12 Softkeys. Eine Strategie kann wie folgt sein: gegeben seien 12 Softkeys (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11) wobei die Anordnung derer auf den meisten Displays so ist, dass in der rechten Spalte 0 bis 5, und in der linken Spalte 6 bis 11 sind. Es liegen sich also gegenüber: 0 und 6, 1 und 7, 2 und 8, 3 und 9, 4 und 10 sowie 5 und 11. Um nun diese Paare beizubehalten löscht man bei der Reduktion von 12 auf 10 Keys das Paar 5/11, bei der weiteren Reduktion von 10 auf 8 Keys das Paar 4/10, bei der weiteren Reduktion von 8 auf 6 Keys das Paar 3/9.

Ein Beispiel für eine Softkey-Maske mit 12 Softkeys könnte wie folgt aussehen:

*   Softkey 0: Funktion A
*   Softkey 1: Funktion B  
*   Softkey 2: Funktion C  
*   Softkey 3: Funktion D  
*   Softkey 4: Funktion E  
*   Softkey 5: Funktion F  
*   Softkey 6: Funktion G  
*   Softkey 7: Funktion H  
*   Softkey 8: Funktion I  
*   Softkey 9: Funktion J  
*   Softkey 10: Funktion K  
*   Softkey 11: Funktion L

Eine mögliche Strategie für die Softkey-Reduktion könnte sein, die Softkeys paarweise zu behalten und dann jeweils das letzte Paar zu entfernen, wenn die Anzahl der Softkeys reduziert wird.

![](https://user-images.githubusercontent.com/69573151/213753461-517b1bef-2608-4c40-8679-921c4a99ed36.png)

Bei einer Reduktion von 12 auf 10 Softkeys würde man das Paar 5/11 entfernen, wobei die Softkeys 0 bis 4 und 6 bis 10 verbleiben.

![](https://user-images.githubusercontent.com/69573151/213754278-dc004bc9-1497-4ae4-ad96-d27389a3194f.png)

Bei einer weiteren Reduktion von 10 auf 8 Softkeys würde man das Paar 4/10 entfernen, wobei die Softkeys 0 bis 3 und 6 bis 9 verbleiben.

![](https://user-images.githubusercontent.com/69573151/213755659-3d57694f-413e-48df-a253-a3a3a89c928e.png)

Bei einer weiteren Reduktion von 8 auf 6 Softkeys würde man das Paar 3/9 entfernen, wobei die Softkeys 0 bis 2 und 6 bis 8 verbleiben.

![](https://user-images.githubusercontent.com/69573151/213755944-66ff8a24-ba9f-4b98-99cd-f683ee9c8265.png)

Diese Strategie ermöglicht es, die wichtigsten Funktionen beizubehalten, während die Anzahl der Softkeys reduziert wird, und sicherzustellen, dass die Funktionen auf dem Display in einer logischen und einfach zu verwendenden Anordnung angezeigt werden.
