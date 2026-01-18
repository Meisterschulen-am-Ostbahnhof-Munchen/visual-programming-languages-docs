# F_FIND

```{index} single: F_FIND
```

<img width="1408" height="240" alt="F_FIND" src="https://github.com/user-attachments/assets/04ca16d1-99bf-4317-8cc7-adf2d6f70af7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_FIND` dient zur Ermittlung der Position des ersten Auftretens einer Zeichenkette (IN2) innerhalb einer anderen Zeichenkette (IN1). Falls die gesuchte Zeichenkette nicht gefunden wird, gibt der Block den Wert 0 zurück. 

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Suche nach der Zeichenkette. Die Eingänge IN1 und IN2 werden mit diesem Ereignis verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Beendigung der Suchoperation. Der Ausgang OUT wird mit diesem Ereignis verknüpft.

### **Daten-Eingänge**
- **IN1** (ANY_STRING): Die Zeichenkette, in der gesucht wird.
- **IN2** (ANY_STRING): Die Zeichenkette, nach der gesucht wird.

### **Daten-Ausgänge**
- **OUT** (ANY_INT): Die Position des ersten Auftretens von IN2 in IN1. Falls nicht gefunden, wird 0 zurückgegeben.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `F_FIND` durchsucht die Zeichenkette IN1 nach dem ersten Auftreten der Zeichenkette IN2. Die Position des ersten Zeichens der gefundenen Zeichenkette wird als Ergebnis zurückgegeben. Falls IN2 nicht in IN1 enthalten ist, wird 0 zurückgegeben.

## Technische Besonderheiten
- Unterstützt beliebige Zeichenketten-Typen (ANY_STRING).
- Gibt einen beliebigen Integer-Typ (ANY_INT) zurück.
- Die Suche ist case-sensitive (Groß-/Kleinschreibung wird beachtet).

## Zustandsübersicht
1. **Idle**: Wartet auf das REQ-Ereignis.
2. **Processing**: Durchsucht IN1 nach IN2.
3. **Completed**: Sendet das CNF-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- Suche nach Teilzeichenketten in Texten.
- Validierung von Eingabedaten.
- Verarbeitung von Zeichenketten in Automatisierungsprozessen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_FIND_STRING` bietet `F_FIND` eine ähnliche Funktionalität, ist jedoch spezifisch für die Suche nach der ersten Position einer Teilzeichenkette.
- Andere Blöcke wie `F_MID` oder `F_LEFT` bieten zusätzliche Funktionen zur Zeichenkettenmanipulation, aber keine Suchfunktion.

## Fazit
Der `F_FIND` Funktionsblock ist ein nützliches Werkzeug zur Suche nach Teilzeichenketten in Automatisierungsanwendungen. Seine einfache und effiziente Implementierung macht ihn ideal für die Integration in komplexere Steuerungslogiken.
