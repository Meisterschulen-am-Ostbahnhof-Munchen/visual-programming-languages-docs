# E_SPLIT (Ereignis-Verteiler)

```{index} single: E_SPLIT (Ereignis-Verteiler)
```

![E_SPLIT Funktionssymbol](https://user-images.githubusercontent.com/69573151/210802227-1615f35d-6ed5-459b-a796-a5ef5fb11452.png)  

* * * * * * * * * *

## 🎧 Podcast

* [Der E_CTU in der IEC 61499: Ereignisgesteuertes Zählen und warum der Minimalist im Maschinenbau überzeugt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_CTU-in-der-IEC-61499-Ereignisgesteuertes-Zhlen-und-warum-der-Minimalist-im-Maschinenbau-berzeugt-e3a9qnq)
* [Der E_CTU-Baustein: Ereignisgesteuertes Hochzählen in der Industrie nach IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_CTU-Baustein-Ereignisgesteuertes-Hochzhlen-in-der-Industrie-nach-IEC-61499-e36846t)
* [Der E_PERMIT-Baustein: Der "Türsteher" für Ereignisse in IEC 61499-Systemen entschlüsselt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_PERMIT-Baustein-Der-Trsteher-fr-Ereignisse-in-IEC-61499-Systemen-entschlsselt-e3681m5)
* [DIN EN 61499-1: Die Lego-Steine für flexible und ereignisgesteuerte Industriesteuerungen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/DIN-EN-61499-1-Die-Lego-Steine-fr-flexible-und-ereignisgesteuerte-Industriesteuerungen-e3681o1)
* [DIN EN 61499-1: Revolution in der Steuerungstechnik – Modulare, ereignisgesteuerte Systeme verstehen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/DIN-EN-61499-1-Revolution-in-der-Steuerungstechnik--Modulare--ereignisgesteuerte-Systeme-verstehen-e367nse)

## 📺 Video

* [Der E_CTU in der IEC 61499: Ereignisgesteuertes Zählen und warum der Minimalist im Maschinenbau ü...](https://www.youtube.com/watch?v=Czizu1DVan8)
* [DIN EN 61499: Industrielle Steuerungen modular und ereignisbasiert mit Funktionsbausteinen meiste...](https://www.youtube.com/watch?v=fD6yS9dQVLY)
* [Ereignisschalter E_SWITCH aus der IEC 61499 (Übung 86)](https://www.youtube.com/watch?v=Gev-kGR4-Tc)
* [EventFBs nach IEC 61499: Legosteine der Automatisierung – So funktionieren Ereignis-Funktionsbaus...](https://www.youtube.com/watch?v=4Z9TjTT78rg)
* [Gesteuerte Verbreitung eines Ereignisses E_PERMIT aus der IEC 61499 (Übung 94)](https://www.youtube.com/watch?v=ry5LTRd9H3M)

## Einleitung
Der **E_SPLIT** ist ein standardkonformer Funktionsbaustein (IEC 61499-1 Annex A) zur Ereignisverteilung, entwickelt unter EPL-2.0 Lizenz. Version 1.0 teilt ein eingehendes Ereignis sequenziell in zwei Ausgangsereignisse auf.

## Schnittstellenstruktur

### **Ereignis-Eingang**
- `EI`: Eingangsereignis (Trigger für die Verteilung)

### **Ereignis-Ausgänge**
- `EO1`: Erstes Ausgangsereignis
- `EO2`: Zweites Ausgangsereignis

## Funktionsweise

1. **Ereignisempfang**:
   - Bei Eingang von `EI` wird der Zustandsautomat aktiviert

2. **Sequenzielle Verarbeitung**:
   - **START-Zustand**: Wartet auf Eingangsereignis
   - **State-Zustand**:
     - Führt `EO1`-Aktion aus (sofort)
     - Führt `EO2`-Aktion aus (unmittelbar danach)
   - Automatische Rückkehr zu START

3. **Ausführungsreihenfolge**:
   - Garantierte Abfolge: EI → EO1 → EO2
   - Deterministisches Timing

![Beispieldiagram](https://user-images.githubusercontent.com/113907476/227972526-0c1d6245-f068-4b58-a4b6-37b9dcb98398.png)


## Technische Besonderheiten

✔ **Strikte Sequenzierung** (EO1 vor EO2)  
✔ **Zustandsbasierte Implementierung** (BasicFB)  
✔ **Echtzeitfähige** Ereignisverarbeitung  
✔ **EPL-2.0 Open-Source** Implementierung  

## Anwendungsszenarien

- **Ablaufsteuerung**: Getaktete Prozessschritte
- **Gerätesteuerung**: Aktivierungssequenzen
- **Sicherheitssysteme**: Verzögerte Notfallroutinen
- **Testautomation**: Trigger für Testsequenzen

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_SPLIT | E_DEMUX | E_MERGE |
|---------------|---------|---------|---------|
| Funktionsprinzip | 1:2 Sequenz | 1:n Verteilung | n:1 Kombination |
| Ereignisreihenfolge | Fest | Adressabhängig | Beliebig |
| Zustandsmodell | BasicFB | Variabel | Keins |

## Fazit

Der E_SPLIT-Baustein bietet eine zuverlässige Lösung für sequenzielle Ereignisverteilung:

- Garantierte Ereignisabfolge
- Einfache aber wirkungsvolle Funktionalität
- Robustes Zustandsmaschinenmodell

 Durch seine deterministische Arbeitsweise eignet er sich besonders für zeitkritische Steuerungsaufgaben und sicherheitsrelevante Anwendungen. Die standardkonforme Implementierung ermöglicht problemlose Integration in IEC 61499-basierte Systeme.