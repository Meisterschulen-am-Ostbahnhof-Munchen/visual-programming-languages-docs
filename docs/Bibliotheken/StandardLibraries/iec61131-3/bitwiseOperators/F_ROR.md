# F_ROR

```{index} single: F_ROR
```

<img width="1364" height="208" alt="F_ROR" src="https://github.com/user-attachments/assets/b26a1c34-8702-476a-9811-0f51ada0efd6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ROR` (Rotate Right) führt eine bitweise Rechtsrotation durch. Er gehört zur Kategorie der standardisierten Bitverschiebungsfunktionen gemäß IEC 61131-3. Der Block rotiert die Eingabedaten um eine angegebene Anzahl von Bits nach rechts und füllt die frei werdenden Bits mit den herausrotierenden Bits auf.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Service-Anfrage, die die Operation auslöst. Wird mit den Daten-Eingängen `IN` und `N` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der durchgeführten Operation. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN`: Der Eingabewert, der rotiert werden soll (Typ: `ANY_BIT`).
- `N`: Die Anzahl der Bits, um die der Eingabewert nach rechts rotiert werden soll (Typ: `ANY_INT`).

### **Daten-Ausgänge**
- `OUT`: Das Ergebnis der Rechtsrotation (Typ: `ANY_BIT`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine bitweise Rechtsrotation des Eingabewertes `IN` um `N` Bits durch. Dabei werden die herausrotierenden Bits auf der linken Seite wieder eingefügt. Dies unterscheidet sich von einer einfachen Rechtsverschiebung, bei der die frei werdenden Bits mit Nullen aufgefüllt werden.

## Technische Besonderheiten
- Unterstützt alle `ANY_BIT`-Datentypen für den Eingabewert `IN` und den Ausgabewert `OUT`.
- Der Parameter `N` kann jeden `ANY_INT`-Datentyp annehmen.
- Die Operation ist unabhängig von der Wortbreite des Eingabewertes.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Kryptografische Operationen, die bitweise Rotationen erfordern.
- Signalverarbeitung, bei denen Daten bitweise manipuliert werden müssen.
- Low-Level-Hardware-Steuerungen, die bitweise Operationen benötigen.

## Vergleich mit ähnlichen Bausteinen
- `F_SHR` (Shift Right): Führt eine Rechtsverschiebung durch, füllt aber die frei werdenden Bits mit Nullen auf.
- `F_ROL` (Rotate Left): Führt eine Linksrotation durch, ähnlich wie `F_ROR`, aber in die entgegengesetzte Richtung.

## Fazit
Der `F_ROR`-Funktionsblock ist ein nützliches Werkzeug für Anwendungen, die bitweise Rotationen erfordern. Seine einfache Schnittstelle und die Unterstützung verschiedener Datentypen machen ihn flexibel einsetzbar. Im Gegensatz zu einfachen Verschiebungsoperationen behält er alle Bits des Eingabewertes bei, was ihn für bestimmte Anwendungen unverzichtbar macht.