# F_DWORD_TO_LWORD

```{index} single: F_DWORD_TO_LWORD
```

<img width="1255" height="181" alt="F_DWORD_TO_LWORD" src="https://github.com/user-attachments/assets/8b697d39-33ef-445c-8626-4e4ece73fda6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_LWORD` dient der Konvertierung eines 32-Bit-Datenwerts (DWORD) in einen 64-Bit-Datenwert (LWORD). Diese Konvertierung ist besonders in Szenarien nützlich, in denen eine Erweiterung der Datenbreite erforderlich ist, um Kompatibilität mit nachfolgenden Verarbeitungsschritten zu gewährleisten.

![F_DWORD_TO_LWORD](F_DWORD_TO_LWORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** (Typ: Event): Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF** (Typ: Event): Signalisiert den erfolgreichen Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (Typ: DWORD): Der 32-Bit-Eingangswert, der in einen 64-Bit-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (Typ: LWORD): Der resultierende 64-Bit-Ausgangswert nach der Konvertierung.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von DWORD zu LWORD durch, indem der 32-Bit-Eingangswert (`IN`) in einen 64-Bit-Wert (`OUT`) umgewandelt wird. Die Konvertierung erfolgt automatisch bei Empfang eines Ereignisses am Eingang `REQ`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist als einfacher FB (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt ohne Datenverlust, da der 32-Bit-Wert in den 64-Bit-Wert eingebettet wird.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Erweiterung der Datenbreite für nachfolgende Verarbeitungsschritte.
- Kompatibilitätsanpassung zwischen Systemen, die unterschiedliche Datenbreiten verwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen (z.B. `F_WORD_TO_DWORD`) ist dieser Funktionsblock speziell für die Konvertierung von 32-Bit- zu 64-Bit-Werten optimiert.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Skalierung oder Offset-Anpassung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_DWORD_TO_LWORD` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 32-Bit- zu 64-Bit-Werten. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine reine Datenbreitenerweiterung benötigt wird.