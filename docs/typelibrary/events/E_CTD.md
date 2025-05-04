# E\_CTD

![E_CTD Diagram](https://user-images.githubusercontent.com/113907528/204893284-f9e75568-aeeb-4000-b4eb-2b0a7ef18187.png)  

* * * * * * * * * *  

## Einleitung  
Der **E_CTD** (Event-Driven Down Counter) ist ein ereignisgesteuerter Abwärtszähler nach dem IEC 61499-Standard. Dieser Funktionsbaustein wird in industriellen Steuerungssystemen eingesetzt, um Zählvorgänge zu realisieren, die durch Ereignisse gesteuert werden.  

## Struktur des E_CTD-Bausteins  

### Schnittstelle (Interface)  

**Eingangsereignisse (Event Inputs):**  
- **CD (Count Down):** Dekrementiert den Zählerstand um 1.  
- **LD (Load):** Lädt einen neuen Startwert in den Zähler.  

**Ausgangsereignisse (Event Outputs):**  
- **CDO (Count Down Output):** Wird ausgelöst, wenn der Zählerstand 0 erreicht.  
- **LDO (Load Output):** Bestätigt das erfolgreiche Laden eines neuen Zählerwerts.  

**Eingangsvariablen (Input Variables):**  
- **PV (Preset Value):** Der Startwert, der bei einem LD-Ereignis geladen wird (Datentyp: INT).  

**Ausgangsvariablen (Output Variables):**  
- **CV (Current Value):** Der aktuelle Zählerstand (Datentyp: INT).  

## Verhalten des E_CTD-Bausteins  

1. **Initialisierung:**  
   - Der Zähler wird mit dem Wert **PV** initialisiert, wenn ein **LD**-Ereignis eintritt.  
   - Das **LDO**-Ereignis wird ausgelöst, um das erfolgreiche Laden zu bestätigen.  

2. **Abwärtszählen:**  
   - Bei jedem **CD**-Ereignis wird der Zählerstand **CV** um 1 verringert.  
   - Wenn **CV** den Wert 0 erreicht, wird das **CDO**-Ereignis ausgelöst.  

3. **Neuladen des Zählers:**  
   - Ein erneutes **LD**-Ereignis setzt **CV** zurück auf **PV** und löst **LDO** aus.  

## Technische Besonderheiten  
- **Ereignisgesteuert:** Der Baustein arbeitet ausschließlich auf Basis von Ereignissen und benötigt keinen zyklischen Aufruf.  
- **Flexible Initialisierung:** Der Startwert **PV** kann jederzeit durch ein **LD**-Ereignis geändert werden.  

## Anwendungsbeispiele  
- **Produktionslinien:** Zählen von produzierten Einheiten.  
- **Verpackungsmaschinen:** Steuerung von Füllvorgängen.  
- **Energiemanagement:** Überwachung von Verbrauchszyklen.  

## Vergleich mit ähnlichen Bausteinen  

| Feature          | E_CTD             | E_CTU (Up Counter) | E_CTUD (Up/Down Counter) |  
|------------------|-------------------|--------------------|--------------------------|  
| Zählrichtung     | Abwärts           | Aufwärts           | Beides                   |  
| Ereignisgesteuert| Ja                | Ja                 | Ja                       |  
| Reset-Funktion   | LD (Neuladen)     | R (Reset)          | R (Reset)                |  

## Fazit  
Der **E_CTD**-Baustein ist ein wesentliches Element in der IEC 61499, das eine zuverlässige und flexible Zählfunktion für industrielle Steuerungen bietet. Seine ereignisgesteuerte Natur macht ihn besonders geeignet für verteilte Systeme, wo zyklische Abfragen nicht praktikabel sind. Durch die klare Schnittstelle und das intuitive Verhalten ist er einfach in bestehende Steuerungskonzepte zu integrieren.
