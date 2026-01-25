# F_DWORD_TO_SINT

```{index} single: F_DWORD_TO_SINT
```

<img width="1248" height="181" alt="F_DWORD_TO_SINT" src="https://github.com/user-attachments/assets/f27122be-9192-4b18-a187-5b5710f2bdcf" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_SINT` dient der Konvertierung eines 32-Bit-DWORD-Wertes in einen 8-Bit-SINT-Wert (vorzeichenbehaftete Ganzzahl). Dieser Baustein ist Teil der IEC 61131-Konvertierungsbibliothek und ermöglicht eine einfache Typumwandlung zwischen diesen Datentypen.

![F_DWORD_TO_SINT](F_DWORD_TO_SINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den erfolgreichen Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (DWORD): Der 32-Bit-Eingangswert, der in einen SINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (SINT): Der konvertierte 8-Bit-SINT-Wert.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert vom Typ DWORD in einen SINT-Wert umwandelt. Die Konvertierung erfolgt durch die eingebaute Funktion `DWORD_TO_SINT`. Nach Abschluss der Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am `OUT`-Ausgang zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der DWORD-Wert außerhalb des darstellbaren Bereichs eines SINT (-128 bis 127) liegt.
- Der Funktionsblock ist ein einfacher Baustein ohne interne Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo DWORD-Werte in kompaktere SINT-Werte umgewandelt werden müssen.
- Datenreduktion, wenn nur der niederwertigste Teil eines DWORD-Wertes benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_DWORD_TO_INT` oder `F_DWORD_TO_USINT` konvertiert dieser Baustein in einen vorzeichenbehafteten 8-Bit-Wert.
- Ähnliche Bausteine für andere Zieltypen sind in der IEC 61131-Konvertierungsbibliothek verfügbar.

## Fazit
Der `F_DWORD_TO_SINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, DWORD-Werte in SINT-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, wo Speicherplatz oder Datenbandbreite optimiert werden müssen. Bei der Verwendung ist auf den möglichen Wertebereich des SINT-Datentyps zu achten, um unerwünschte Datenverluste zu vermeiden.