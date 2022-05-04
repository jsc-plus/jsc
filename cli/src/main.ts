
import commander from 'commander';
import * as C from "./C/parse"

commander.program.command('gen-c <inFile> <outDir> <moduleName>')
        .description('quick generate pb java')
        .usage("gen-c <inFile> <outDir> <moduleName>")
        .action(function (inFile: string, outDir: string, moduleName: string) {
                C.parse(inFile, outDir, moduleName)
        });


commander.program.parse(process.argv);