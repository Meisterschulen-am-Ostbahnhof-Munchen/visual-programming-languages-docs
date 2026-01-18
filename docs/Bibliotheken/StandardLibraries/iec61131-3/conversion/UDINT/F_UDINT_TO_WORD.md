# F_UDINT_TO_WORD

```{index} single: F_UDINT_TO_WORD
```

<img width="1449" height="216" alt="F_UDINT_TO_WORD" src="https://github.com/user-attachments/assets/31e92c35-2b63-4389-99d2-83dc3fda9dc5" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_WORD` dient der Konvertierung eines 32-Bit unsignierten Integer-Werts (UDINT) in einen 16-Bit unsignierten Integer-Wert (WORD). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (UDINT): Der 32-Bit unsignierte Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WORD): Der resultierende 16-Bit unsignierte Integer-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von UDINT zu WORD durch, indem der Algorithmus `REQ` ausgeführt wird. Dabei wird der Eingangswert `IN` vom Typ UDINT in einen WORD-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung erfolgt synchron mit dem Ereignis `REQ`, und das Ergebnis wird mit dem Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung schneidet die höherwertigen 16 Bits des UDINT-Werts ab, da ein WORD nur 16 Bits umfasst.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand. Die Konvertierung wird bei jedem Ereignis `REQ` neu ausgeführt.

## Anwendungsszenarien
- Datenreduktion von 32-Bit auf 16-Bit in eingebetteten Systemen.
- Kompatibilität mit älteren Systemen, die nur 16-Bit-Daten verarbeiten können.
- Speicheroptimierung in ressourcenbeschränkten Umgebungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_DINT_TO_WORD` oder `F_INT_TO_WORD` verarbeitet dieser Baustein unsignierte Werte.
- Ähnliche Bausteine wie `F_UDINT_TO_DWORD` führen keine Reduktion der Bitbreite durch.

## Fazit
Der `F_UDINT_TO_WORD` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 32-Bit unsignierte Integer-Werte in 16-Bit unsignierte Integer-Werte umzuwandeln. Er ist besonders nützlich in Szenarien, wo eine Reduktion der Datenbreite erforderlich ist, ohne die grundlegende Semantik der Daten zu verändern.