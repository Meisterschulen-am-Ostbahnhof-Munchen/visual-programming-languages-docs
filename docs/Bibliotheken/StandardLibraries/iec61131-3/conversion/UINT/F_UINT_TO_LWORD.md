# F_UINT_TO_LWORD

```{index} single: F_UINT_TO_LWORD
```

<img width="1452" height="216" alt="F_UINT_TO_LWORD" src="https://github.com/user-attachments/assets/be6bea7a-7598-41df-9c89-9d0b6d2272ef" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_LWORD` dient der Konvertierung eines `UINT`-Wertes (16-Bit unsigned integer) in einen `LWORD`-Wert (64-Bit unsigned integer). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten unterschiedlicher Bitbreiten verarbeitet oder übertragen werden müssen.

![F_UINT_TO_LWORD](F_UINT_TO_LWORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `UINT`, der in einen `LWORD`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `LWORD`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung mittels des Algorithmus `REQ` durch, der bei Auslösung des Ereignisses `REQ` aktiviert wird. Der Algorithmus wandelt den `UINT`-Eingangswert `IN` in einen `LWORD`-Wert um und weist diesen dem Ausgang `OUT` zu. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Datenverlust, da der `LWORD`-Typ einen größeren Wertebereich als `UINT` abdeckt.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wo unterschiedliche Datentypen verarbeitet werden müssen.
- Integration in größere Funktionsblock-Netzwerke, die Daten unterschiedlicher Bitbreiten verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_UINT_TO_LWORD` spezialisiert auf die Konvertierung von `UINT` zu `LWORD` und bietet somit eine optimierte und typsichere Lösung.
- Andere Konvertierungsblöcke könnten zusätzliche Funktionen wie Fehlerbehandlung oder Überlaufprüfung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_UINT_TO_LWORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, `UINT`-Werte in `LWORD`-Werte umzuwandeln. Seine Einfachheit und Determinismus machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen. Für komplexere Anforderungen, wie Fehlerbehandlung, sollten jedoch erweiterte Funktionsblöcke in Betracht gezogen werden.